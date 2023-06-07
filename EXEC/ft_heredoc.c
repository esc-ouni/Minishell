/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:39:29 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/07 11:20:09 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_gen_name()
{
	return (NULL);
}

static int	ft_heredoc_write(int fd, char *delimiter, t_struct *cable)
{
	char	*line;

	while (1)
	{
		line = readline(">");
		if (!line || !ft_strlen(line))
			break ;
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
	/*gen a name */
	char	*name;

	dup2(cable->tmp_fd_in, 0);
	name = "GEN";
	/*see if that name exist*/
	/*create file with that name*/

	/*open*/
	int fd = open(name, O_CREAT | O_TRUNC | O_WRONLY, 0664);
	/*write in it*/
	ft_heredoc_write(fd, delimiter, cable);
	/*close it*/
	close(fd);
	cmd->fd_in = open(name, O_RDONLY);
	/*open it and dup*/
	return (0);
}
