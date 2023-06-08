/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:11:40 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/08 14:28:54 by msamhaou         ###   ########.fr       */
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

static	void	ft_herdoc_p(t_file *file, int pid, int *pfd, t_struct *cable)
{
	close(pfd[1]);
	if (!file->next)
		dup2(pfd[0], STDIN_FILENO);
	waitpid(pid, NULL, 0);
	close(pfd[0]);
}

int	ft_heredoc_proc(t_file *file, t_struct *cable)
{
	int	pfd[2];
	int	pid;
	int	t;

	t = g_var;
	g_var = 5;
	pipe(pfd);
	pid = fork();
	if (!pid)
	{
		signal_dfl(cable);
		close(pfd[0]);
		dup2(cable->tmp_fd_in, STDIN_FILENO);
		ft_heredoc_write(pfd[1], file->filename, cable);
		close(pfd[1]);
		exit(0);
	}
	else
		ft_herdoc_p(file, pid, pfd, cable);
	g_var = t;
	return (0);
}
