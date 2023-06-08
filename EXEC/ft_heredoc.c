/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:39:29 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/07 22:26:10 by msamhaou         ###   ########.fr       */

/*   Updated: 2023/06/07 19:35:07 by idouni           ###   ########.fr       */
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
			continue ;
		if (!ft_strcmp(line, delimiter))
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	return (0);
}

int	ft_heredoc(t_cmd *cmd, char *delimiter, t_struct *cable)
{
	char	*name;
	int		fd;
	int		*pipe;

	dup2(cable->tmp_fd_in, 0);
	name = "obj/GEN";
	fd = open(name, O_CREAT | O_TRUNC | O_WRONLY, 0664);
	if (fd < 0)
		return (perror(""), exit(1), 1);
	ft_heredoc_write(fd, delimiter, cable);
	close(fd);
	fd = open(name, O_RDONLY);
	return (fd);
}

int	ft_heredoc_proc(char *delimiter, t_struct *cable)
{
	int	pid;
	int fd;

	fd = open("GEN", O_TRUNC|O_CREAT|O_WRONLY, 0664);
	pid = fork();
	if (!pid)
	{
		ft_heredoc_write(fd, delimiter, cable);
		exit(0);
	}
	else
	{
		waitpid(pid, NULL, 0);
		close(fd);
		fd = open("GEN", O_RDONLY);
		return (fd);
	}
}
