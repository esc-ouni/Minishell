/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_12.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:09:45 by idouni            #+#    #+#             */
/*   Updated: 2023/06/11 22:25:49 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prm(int argc, char **argv, char **env)
{
	(void)argv;
	if (argc == 2)
	{
		if (!argv[1] || !ft_strlen(argv[1]))
			exit(0);
		execve("/bin/bash", argv, env);
		exit(0);
	}
	else if (argc > 1)
		exit(0);
}

void	sig_h(int sig)
{
	if (sig == SIGINT && g_var == 1)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT && g_var == 1)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT && !g_var)
	{
		g_var = 131;
		write(1, "^\\Quit : 3\n", 12);
		rl_redisplay();
	}
	else if (sig == SIGINT && !g_var)
	{
		g_var = 130;
		write(1, "^C\n", 4);
		rl_on_new_line();
	}
	else if (sig == SIGINT && g_var == 17)
		g_var = 256;
	else if (sig == SIGQUIT && g_var == 17)
	{
		// rl_on_new_line();
		// rl_redisplay();
	}
}

void	strt1(t_struct *cable)
{
	int				t_fd;
	struct termios	terminal_c;

	t_fd = open("/dev/tty", O_RDONLY);
	if (t_fd == -1)
	{
		perror("Error getting terminal fd");
		ft_collectorclear(cable->collector, ALL);
	}
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
	if (signal(SIGQUIT, sig_h) == SIG_ERR)
	{
		perror("Error ignoring a signal");
		ft_collectorclear(cable->collector, ALL);
	}
}

void	strt(t_struct *cable)
{
	strt1(cable);
	strt2(cable);
}
