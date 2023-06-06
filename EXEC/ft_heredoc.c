/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:39:29 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/06 15:10:29 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_gen_name()
{
	return (NULL);
}

static int	ft_heredoc_write(int fd, char *delimiter)
{
	char	*line;
	char	*delim;

	delim = ft_strjoin(delimiter, "\n");
	line = get_next_line(0);
	while (line)
	{
		if (!ft_strncmp(line, delim, ft_strlen(line)))
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
	}
	free(delim);
	return (0);
}

int	ft_heredoc(t_cmd *cmd, char *delimiter)
{
	/*gen a name */
	char	*name;

	name = "GEN";
	/*see if that name exist*/
	/*create file with that name*/

	/*open*/
	int fd = open(name, O_CREAT | O_TRUNC | O_WRONLY);
	/*write in it*/
	ft_heredoc_write(fd, delimiter);
	/*close it*/
	close(fd);
	cmd->fd_in = open(name, O_RDONLY);
	/*open it and dup*/
	return (0);
}
