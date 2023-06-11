/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:11:40 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/11 22:28:53 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static int	ft_heredoc_write(int fd, char *delimiter, t_struct *cable)
{
	char	*line;

	while (1)
	{
		line = readline(">");
		if (!line)
			break ;
		if (!ft_strlen(line))
		{
			free(line);
			continue ;
		}
		if (!ft_strcmp(line, delimiter))
		{
			free(line);
			break ;
		}
		line = s_expander(cable, line);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
	}
	return (0);
}

static int	ft_herdoc_p(t_struct *cable, t_file *file, int pid, int *pfd)
{
	close(pfd[1]);
	if (!file->next)
		if (dup2(pfd[0], STDIN_FILENO) == -1)
			return (perror(""), ft_collectorclear(cable->collector, ALL), -1);
	waitpid(pid, NULL, 0);
	if (g_var == 256)
	{
		cable->exit_val = 1;
		return (-1);
	}
	close(pfd[0]);
	return (0);
}

int	ft_heredoc_proc(t_file *file, t_struct *cable)
{
	int	pfd[2];
	int	pid;
	int	t;

	t = g_var;
	g_var = 17;
	pipe(pfd);
	pid = fork();
	if (!pid)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_DFL);
		close(pfd[0]);
		if (dup2(cable->tmp_fd_in, STDIN_FILENO) == -1)
			exit(1);
		ft_heredoc_write(pfd[1], file->filename, cable);
		close(pfd[1]);
		exit(0);
	}
	else
		if (ft_herdoc_p(cable, file, pid, pfd) == -1)
		{
			g_var = t;	
			return (-1);
		}
	return (0);
}
