/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:11:33 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/11 12:27:17 by msamhaou         ###   ########.fr       */
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
		if (files->next)
			close(cmd->fd_out);
		files = files->next;
	}
	return (0);
}

int	ft_redirect_child(t_cmd *cmd, int *fd, t_struct *cable)
{
	if (cmd->out_files)
	{
		ft_open_out_files(cmd);
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
		{
			perror("");
			exit(1);
		}
	}
	else
	{
		if (cmd->next)
		{
			if (dup2(fd[1], STDOUT_FILENO) == -1)
			{
				perror("");
				exit(1);
			}
		}
		else
			if (dup2(cable->tmp_fd_out, STDOUT_FILENO) == -1)
			{
				perror("");
				exit(1);
			}
	}
	return (0);
}

void	ft_cmd_not(int *fd, t_struct *cable)
{
	if (dup2(cable->tmp_err, STDERR_FILENO) == -1)
		exit(1);
	ft_putendl_fd("cmd does not exist", STDERR_FILENO);
	close(fd[1]);
	close(2);
	close(1);
	exit(127);
}

int	ft_child(t_cmd *cmd, int *fd, t_struct *cable)
{
	close(fd[0]);
	ft_redirect_child(cmd, fd, cable);
	if (cmd->builtflag == NOT)
		ft_cmd_not(fd, cable);
	if (cmd->builtflag && (cmd->builtflag != SYS))
	{
		ft_builtin(cmd, cable);
		close(fd[1]);
		close(1);
		exit (0);
	}
	else if (cmd->builtflag == SYS)
	{
		if (execve(cmd->cmd_path, cmd->cmd, cable->env) < 0)
			ft_collectorclear(cable->collector, ALL);
		exit(0);
	}
	return (1);
}
