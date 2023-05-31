/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 21:10:34 by msamhaou          #+#    #+#             */
/*   Updated: 2023/05/31 12:44:24 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_norm_sucks(int ac, char **av)
{
	(void)av;
	if (ac > 1)
		exit (0);
}

void	reset_io(t_collector **collector, t_init *inval)
{
	dup2(inval->tmp_fd_out, 1);
	dup2(inval->tmp_fd_in, 0);
	// if (dup2(inval->tmp_fd_in, 0) == -1)
	// {
	// 	perror("Error resetting input stream");
	// 	ft_collectorclear(collector);
	// 	exit (1);
	// }
	// if (dup2(inval->tmp_fd_out, 1) == -1)
	// {
	// 	perror("Error resetting output stream");
	// 	ft_collectorclear(collector);
	// 	exit (1);
	// }
}

void	strt(t_collector **collector)
{
	int				err;
	int				t_fd;
	struct termios	terminal_c;

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

t_init	*ft_init(t_collector **collector, char **env)
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
