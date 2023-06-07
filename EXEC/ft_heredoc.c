/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:39:29 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/07 16:41:59 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_heredoc_write(int fd, char *delimiter, t_struct *cable)
{
	char	*line;
	int 	t;

	t = g_var;
	g_var = 4;
	while (1)
	{
		line = readline(">");
		if (!line)
			break ;
		// if (!ft_strlen(line))
		// 	continue ;
		if (!ft_strcmp(line, delimiter))
		{
			free(line);
			break ;
		}
		line = s_expander(cable, line);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		// free(line);
	}
	g_var = t;
	return (0);
}

int	ft_heredoc(t_cmd *cmd, char *delimiter, t_struct *cable)
{
	char	*name;
	int		fd;

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
