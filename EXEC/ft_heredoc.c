/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:11:40 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/08 13:48:08 by idouni           ###   ########.fr       */
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

int	ft_heredoc_proc(t_file *file, t_struct *cable)
{
	int	pfd[2];
	int	pid;
	int t;

	t = g_var;
	g_var = 5;
	pipe(pfd);
	pid = fork();
	if (!pid)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		close(pfd[0]);
		dup2(cable->tmp_fd_in, STDIN_FILENO);
		ft_heredoc_write(pfd[1], file->filename, cable);
		close(pfd[1]);
		exit(0);
	}
	else
	{
		close(pfd[1]);
		if (!file->next)
			dup2(pfd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
		g_var = t;
		close(pfd[0]);
		return (0);
	}
}
