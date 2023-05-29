/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 18:35:34 by msamhaou          #+#    #+#             */
/*   Updated: 2023/05/28 16:09:56 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_exit_val;

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
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ft_quit(t_built flag, t_init *init)
{
	if (flag == EXT)
		write(1, "exit\n", 5);
	ft_end_free(&(init->envlst), (init->myenv), init);
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

t_init	*ft_init(t_collector **collector,char **env)
{
	t_init	*res;

	g_exit_val = 0;
	res = NULL;
	res = h_malloc(collector, sizeof(t_init), res);
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


void strt(t_collector **collector)
{
	int	err;
	int t_fd;
	struct termios terminal_c;

	err = 0;
	t_fd = open("/dev/tty", O_RDONLY);
	if (t_fd == -1)
        perror("Error getting terminal fd"), err = 1;
    if (tcgetattr(t_fd, &terminal_c) < 0) 
        perror("Error getting terminal attr"), err = 1;
    terminal_c.c_lflag &= ~ECHOCTL;
	if (tcsetattr(t_fd, 0, &terminal_c) < 0)
        perror("Error setting terminal attr"), err = 1;
	if (signal(SIGINT, sig_handle) == SIG_ERR)
        perror("Error handling a signal"), err = 1;
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
        perror("Error ignoring a signal"), err = 1;
	if (err)
	{
		ft_collectorclear(collector);
        exit (1);	
	}
}

void	reset_io(t_collector	**collector, t_init	*inval)
{
	if (dup2(inval->tmp_fd_in, 0) == -1)
	{
		perror("Error resetting input stream");
		ft_collectorclear(collector);
		exit (1);
	}
	if (dup2(inval->tmp_fd_out, 1) == -1)
	{
		perror("Error resetting output stream");
		ft_collectorclear(collector);
		exit (1);
	}
	
}

int	main(int ac, char **av, char **env)
{
	t_init	*inval;
	t_collector	*collector;
	char *s;

	collector = NULL;
	strt(&collector);
	ft_norm_sucks(ac, av);
	inval = ft_init(&collector, env);
	while (1)
	{
		reset_io(&collector, inval);
		s = prompt();
		inval->cmd = parser2(&collector \
			, parser(&collector, &(inval->envlst), s));
		emplify(&collector, inval->cmd);
		if (!inval->cmd)
			continue ;
		ft_execution(inval);
	}
}
