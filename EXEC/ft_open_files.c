/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 23:10:01 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/19 18:57:40 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_open_file_case(t_file *file, t_cmd *cmd, t_struct *cable)
{
	int	is_here;

	is_here = 0;
	if (file->o_flag == O_APPEND)
	{
		is_here = 1;
		if (ft_heredoc_proc(file, cable) == -1)
			return (-1);
		cmd->fd_in = -2;
	}
	else if (file->o_flag == O_TRUNC)
	{
		cmd->fd_in = open(file->filename, O_RDONLY);
		if (cmd->fd_in < 0 && !is_here)
			return (perror(file->filename), -1);
		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
			return (perror("dup"), ft_close_fdtmp(cable), \
				ft_collectorclear(cable->collector, ALL), -1);
	}
	if (file->next)
		ft_close(cable, cmd->fd_in);
	return (0);
}

int	ft_open_in_file(t_cmd *cmd, t_struct *cable)
{
	t_file	*files;
	int		op;

	files = cmd->in_files;
	cmd->fd_in = -1;
	op = 0;
	while (files)
	{
		op = ft_open_file_case(files, cmd, cable);
		if (op < 0)
			return (op);
		files = files->next;
	}
	return (0);
}
