/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:11:33 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/14 13:34:07 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_open_out_files(t_struct *cable, t_cmd *cmd)
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
			ft_close(cable, cmd->fd_out);
		files = files->next;
	}
	return (0);
}

int	ft_redirect_child(t_struct *cable, t_cmd *cmd, int *fd)
{
	if (cmd->out_files)
	{
		ft_open_out_files(cable, cmd);
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
	}
	return (0);
}

void	ft_cmd_not(t_struct *cable, int *fd)
{
	ft_putendl_fd("cmd does not exist", STDERR_FILENO);
	ft_close(cable, fd[1]);
	ft_close(cable, 0);
	ft_close(cable, 1);
	exit(127);
}

int	ft_child(t_cmd *cmd, int *fd, t_struct *cable)
{
	signal_dfl();
	if (cmd->builtflag == NOT && cmd->cmd && cmd->cmd[0])
		ft_cmd_not(cable, fd);
	ft_close(cable, fd[0]);
	ft_redirect_child(cable, cmd, fd);
	if (cmd->builtflag && (cmd->builtflag != SYS))
	{
		ft_builtin(cmd, cable);
		ft_close(cable, 1);
		exit(0);
	}
	else if (cmd->builtflag == SYS)
	{
		if (execve(cmd->cmd_path, cmd->cmd, cable->env) == -1)
		{
			ft_putendl_fd("cmd does not exist", STDERR_FILENO);
			ft_collectorclear(cable->collector, ALL);
		}
		ft_close(cable, fd[1]);
		exit(0);
	}
	return (1);
}
