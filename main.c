/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 18:35:34 by msamhaou          #+#    #+#             */
/*   Updated: 2023/05/22 20:03:39 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_builtin(t_cmd *lol, char **myenv)
{
	if (lol->builtflag == ECH)
		ft_echo(lol);
	else if (lol->builtflag == PWD)
		ft_pwd();
	else if (lol->builtflag == ENV)
		ft_env(myenv);
	return (0);
}

int	ft_open_out_files(t_cmd *lol)
{
	t_file	*files;

	files = lol->out_files;
	while (files)
	{
		lol->cmd_fdout = open(files->filename, O_CREAT
				| files->o_flags | O_WRONLY, 0664);
		if (lol->cmd_fdout < 0)
			return (perror(""), exit(1), 1);
		files = files->next;
	}
	return (0);
}

int	ft_open_in_file(t_cmd *lol)
{
	t_file	*files;

	files = lol->in_files;
	while (files)
	{
		lol->cmd_fdin = open(files->filename, O_RDONLY);
		if (files->o_flags == O_APPEND)
			ft_heredoc(lol, files->filename);
		if (lol->cmd_fdin < 0)
		{
			g_exit_val = 1;
			return (perror(""), 1);
		}
		files = files->next;
	}
	return (0);
}

void	ft_free_pos(char **strp, int pos)
{
	while (pos--)
		free(strp[pos]);
	free(strp);
}

/********************SIGNALES********************/

void	sig_handle(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		// rl_on_new_line();
		// rl_replace_line("", 0);
		// rl_redisplay();
	}
}

void	ft_quit(t_built flag)
{
	if (flag == EXT)
		write(1, "exit\n", 5);
	exit(0);
}
/********************SIGNALES********************/

int	ft_set_path(t_cmd *cmd, char **myenv, t_env *env_lst)
{
	t_cmd	*head;

	if (!cmd->cmd[0])
		return(0);
	head = cmd;
	while (cmd)
	{
		cmd->myenv = env_lst;
		if (!ft_strchr(cmd->cmd[0], '/'))
			cmd->cmd_path = ft_get_path(cmd->cmd, myenv);
		else
			cmd->cmd_path = cmd->cmd[0];
		cmd = cmd->next;
	}
	return (1);
}

void	ft_execution(t_cmd *cmd, t_env **env_lst, char ***myenv, t_init *init)
{
	ft_set_path(cmd, *myenv, *env_lst);
	while (cmd)
	{
		cmd->tty_in = init->tmp_fd_in;
		ft_fork(cmd, myenv, env_lst);
		cmd = cmd->next;
	}
}

void	ft_free_env_lst(t_env **env_lst)
{
	t_env	*tmp;

	while (*env_lst)
	{
		tmp = *env_lst;
		*env_lst = (*env_lst)->next;
		free(tmp);
	}
}

void	ft_end_free(t_env **env_lst, char **myenv, t_init *init_val)
{
	if (myenv)
		ft_free_stringp(myenv);
	if (*env_lst)
		ft_free_env_lst(env_lst);
	if (init_val)
		free(init_val);
	exit(0);
}

t_init	*ft_init(char **env)
{
	t_init	*res;

	g_exit_val = 0;
	res = malloc(sizeof(t_init));
	if (!res)
		exit(1);
	res->collector = NULL;
	res->tmp_fd_in = dup(STDIN_FILENO);
	res->tmp_fd_out = dup (STDOUT_FILENO);
	if (res->tmp_fd_in < 0 || res->tmp_fd_out < 0)
		exit(0);
	res->myenv_list = ft_set_env_list(env);
	res->myenv = ft_set_env(res->myenv_list);
	return (res);
}

void	ft_norm_sucks(int ac, char **av)
{
	(void)av;
	(void)ac;
}

int	main(int ac, char **av, char **env)
{
	t_init	*inval;

	ft_norm_sucks(ac, av);
	inval = ft_init(env);
	while (1)
	{
		dup2(inval->tmp_fd_in, 0);
		dup2(inval->tmp_fd_out, 1);
		signal(SIGINT, sig_handle);
		signal(SIGQUIT, SIG_IGN);
		inval->cmd = parser2(&(inval->collector) \
			, parser(&(inval->collector), &(inval->myenv_list)));
		emplify(&(inval->collector), inval->cmd);
		if (!inval->cmd)
			continue ;
		ft_execution(inval->cmd, &(inval->myenv_list), &(inval->myenv), inval);
	}
	ft_end_free(&(inval->myenv_list), (inval->myenv), inval);
}
