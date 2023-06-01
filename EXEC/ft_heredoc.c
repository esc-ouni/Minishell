/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 18:27:11 by msamhaou          #+#    #+#             */
/*   Updated: 2023/05/30 13:58:01 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_heredoc_child(int *fd, char *delimiter)
{
	char	*line;
	char	*delim;

	delim = ft_strjoin(delimiter, "\n");
	close (fd[0]);
	line = get_next_line(0);
	while (line)
	{
		if (!ft_strncmp(line, delim, ft_strlen(line)))
		{
			free(line);
			exit(0);
		}
		write(fd[1], line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
	}
	free(delim);
	exit(0);
	return (0);
}

int	ft_heredoc(t_cmd *cmd, char *delimiter)
{
	int		pid;
	int		fd[2];

	dup2(cmd->tty_in, STDIN_FILENO);
	pipe(fd);
	pid = fork();
	if (!pid)
	{
		ft_heredoc_child(fd, delimiter);
	}
	else
	{
		close(fd[1]);
		cmd->cmd_fdin = dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
		close(fd[0]);
	}
	return (0);
}
