/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 18:35:34 by msamhaou          #+#    #+#             */
/*   Updated: 2023/05/12 02:34:31 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	siglol = 0;

int	ft_builtin(t_cmd *lol, t_env *env_lst, char **myenv)
{
	if (lol->builtflag == ECH)
		ft_echo(lol);
	else if (lol->builtflag == PWD)
		ft_pwd();
	else if (lol->builtflag == ENV)
		ft_env(myenv);
	return(0);
}


int	ft_open_out_files(t_cmd *lol)
{
	t_file	*files;

	files = lol->out_files;
	while (files)
	{
		lol->cmd_fdout = open(files->filename, O_CREAT | O_TRUNC | O_WRONLY , 0664);
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
		if (lol->cmd_fdin < 0)
			return (perror(""), 1);
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
		// write(1, "\n", 1);
		// rl_on_new_line();
		// rl_replace_line("", 0);/*should be one after history setup*/
		// rl_redisplay();
		// prompt();
		// siglol = 1;
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

	head = cmd;
	while (cmd)
	{
		cmd->myenv = env_lst;
		cmd->cmd_path = ft_get_path(cmd->cmd, myenv);
		cmd = cmd->next;
	}
	return (1);
}
void	ft_execution(t_cmd *cmd, t_env **env_lst,char ***myenv)
{
		ft_set_path(cmd, *myenv,env_lst);
		while (cmd)
		{
			ft_fork(cmd, myenv, env_lst);
			cmd = cmd->next;
		}
}
int main(int ac, char **av, char **env)
{
	(void)av;
	(void)ac;
	int		tmp_fd_in;
	int		tmp_fd_out;
	char	**myenv;
	t_env	*myenv_list;
	t_cmd	*cmd;
	int		i;
	
	i = 0;
	tmp_fd_in = dup(STDIN_FILENO);
	tmp_fd_out = dup (STDOUT_FILENO);
	myenv_list = ft_set_env_list(env);
	myenv = ft_set_env(myenv_list, myenv);
	while (1)
	{
		i = 0;
		siglol = 0;
		dup2(tmp_fd_in, 0);
		dup2(tmp_fd_out, 1);
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		cmd = parser2(parser());
		emplify(cmd, env);
		if (!cmd->cmd[0])
			continue ;
		ft_execution(cmd, &myenv_list, &myenv);
	}
}
