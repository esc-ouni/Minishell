/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_12.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:09:45 by idouni            #+#    #+#             */
/*   Updated: 2023/06/06 15:18:08 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_h(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	strt1(t_struct *cable, int t_fd)
{
	struct termios	terminal_c;

	if (tcgetattr(t_fd, &terminal_c) < 0)
	{
		perror("Error getting terminal attr");
		ft_collectorclear(cable->collector, ALL);
	}
	terminal_c.c_lflag &= ~ECHOCTL;
	if (tcsetattr(t_fd, 0, &terminal_c) < 0)
	{
		perror("Error setting terminal attr");
		ft_collectorclear(cable->collector, ALL);
	}
}

void	strt2(t_struct *cable)
{
	if (signal(SIGINT, sig_h) == SIG_ERR)
	{
		perror("Error handling a signal");
		ft_collectorclear(cable->collector, ALL);
	}
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		perror("Error ignoring a signal");
		ft_collectorclear(cable->collector, ALL);
	}
}

void	strt(t_struct *cable)
{
	int				err;
	int				t_fd;

	err = 0;
	t_fd = open("/dev/tty", O_RDONLY);
	if (t_fd == -1)
	{
		perror("Error getting terminal fd");
		ft_collectorclear(cable->collector, ALL);
	}
	strt1(cable, t_fd);
	strt2(cable);
}