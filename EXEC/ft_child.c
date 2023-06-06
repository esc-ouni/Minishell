/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:22:24 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/06 15:04:21 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_open_out_files(t_cmd *cmd)
{
	t_file	*files;

	files = cmd->out_files;
	while (files)
	{
		cmd->fd_out = open(files->filename, O_CREAT
				| files->o_flag | O_WRONLY, 0664);
		if (cmd->fd_out < 0)
			return (perror(""), exit(1), 1);
		files = files->next;
	}
	return (0);
}

int	ft_redirect_child(t_cmd *cmd, t_struct *cable)
{
	if (cmd->out_files)
	{
		ft_open_out_files(cmd);
		if (dup2(cmd->fd_out, STDOUT_FILENO) < 0)
			exit(1);
	}
	else
	{
		if (cmd->next)
		{
			if (dup2(cmd->pipe_fd[1], STDOUT_FILENO) < 0)
				exit(1);
		}
		else
			dup2(cable->tmp_fd_out, STDOUT_FILENO);
	}
	return (0);
}

int	ft_child(t_cmd *cmd, t_struct *cable)
{
	close(cmd->pipe_fd[0]);
	// if (init->err_in)
	// 	exit(1);
	ft_redirect_child(cmd, cable);
	if (cmd->builtflag)
	{
		ft_builtin(cmd, cable);
		exit (0);
	}
	else if (cmd->builtflag == NOT)
	{
		if ((execve(cmd->cmd_path, cmd->cmd, cable->env) < 0) \
			&& !cmd->builtflag)
		{
			if (cmd->cmd[0])
				ft_putendl_fd("cmd does not exist", 2);
			close(cmd->pipe_fd[1]);
			exit(1);
		}
		exit(0);
	}
	return (1);
}
