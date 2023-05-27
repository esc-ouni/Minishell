/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 18:35:34 by msamhaou          #+#    #+#             */
/*   Updated: 2023/05/27 18:49:18 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_builtin(t_cmd *lol, t_init *init)
{
	if (lol->builtflag == ECH)
		ft_echo(lol);
	else if (lol->builtflag == PWD)
		ft_pwd();
	else if (lol->builtflag == ENV)
		ft_env(init->myenv);
	else if (lol->builtflag == EXPT && !lol->cmd[1])
		ft_printlst(init->exp_lst);
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
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
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
		if (cmd->cmd[0])
		{
		cmd->myenv = env_lst;
		if (!ft_strchr(cmd->cmd[0], '/'))
			cmd->cmd_path = ft_get_path(cmd->cmd, myenv);
		else
			cmd->cmd_path = cmd->cmd[0];
		}
		cmd = cmd->next;
	}
	return (1);
}

void	ft_execution(t_init *init)
{
	int	cmd_num;

	ft_set_path(init->cmd, init->myenv, init->envlst);
	cmd_num = init->cmd->num_cmds;
	while (init->cmd)
	{
		init->cmd->tty_in = init->tmp_fd_in;
		ft_fork(init->cmd, init);
		init->cmd = init->cmd->next;
	}
	while (cmd_num--)
		wait(&g_exit_val);
}

void	ft_free_env_lst(t_env **env_lst)
{
	t_env	*tmp;

	while (*env_lst)
	{
        free((*env_lst)->str);
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
    if (init_val->exp_lst)
        ft_free_env_lst(&init_val->exp_lst);
	if (init_val)
		free(init_val);
	rl_clear_history();
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
	res->envlst = ft_set_env_list(env);
    res->exp_lst = ft_set_export_lst(res->envlst);
	res->myenv = ft_set_env(res->envlst);
	res->err_in = 0;
	return (res);
}

void	ft_norm_sucks(int ac, char **av)
{
	(void)av;
	if (ac > 1)
		exit (0);
}

void    foo()
{
    system("leaks minishell");
}

void strt(t_collector **collector)
{
	struct termios terminal_c;

    if (tcgetattr(1, &terminal_c) < 0) 
	{
        perror("Error getting terminal attr");
		ft_collectorclear(collector);
        exit (1);
    }
    terminal_c.c_lflag &= ~ECHOCTL;
	if (tcsetattr(1, 0, &terminal_c) < 0)
	{
        perror("Error setting terminal attr");
		ft_collectorclear(collector);
        exit (1);
    }
	else if (signal(SIGINT, sig_handle) == SIG_ERR)
	{
        perror("Error handling a signal");
		ft_collectorclear(collector);
        exit (1);
	}
	else if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
        perror("Error ignoring a signal");
		ft_collectorclear(collector);
        exit (1);
	}
}

int	main(int ac, char **av, char **env)
{
	t_init	*inval;
	char *s;

	strt(&(inval->collector));
	ft_norm_sucks(ac, av);
	inval = ft_init(env);
	while (1)
	{
		dup2(inval->tmp_fd_in, 0);
		dup2(inval->tmp_fd_out, 1);
		s = prompt();
		inval->cmd = parser2(&(inval->collector) \
			, parser(&(inval->collector), &(inval->envlst), s));
		emplify(&(inval->collector), inval->cmd);
		if (!inval->cmd)
			continue ;
		ft_execution(inval);
	}
	ft_end_free(&(inval->envlst), (inval->myenv), inval);
}
