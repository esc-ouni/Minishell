/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:43:54 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/16 15:43:35 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_parent(t_struct *cable, t_cmd *cmd, int *fd)
{
	ft_close(cable, fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		return (perror("dup2"), ft_close_fdtmp(cable), \
			ft_collectorclear(cable->collector, ALL), 1);
	if (cmd->fd_in != -1)
		ft_close(cable, cmd->fd_in);
	ft_close(cable, fd[0]);
	return (0);
}

static int	ft_first_redirection(t_cmd *cmd, t_struct *cable)
{
	int	op;

	op = 0;
	if (cmd->in_files)
	{
		op = ft_open_in_file(cmd, cable);
		if (op == -1)
			cable->exit_val = 1;
	}
	return (op);
}

int	ft_open_pipe(t_struct *cable, int *fd)
{
	if (pipe(fd) == -1)
		return (perror("pipe"), ft_close_fdtmp(cable), \
			ft_collectorclear(cable->collector, ALL), -1);
	return (0);
}

int	ft_fork(t_cmd *cmd, t_struct *cable)
{
	int	fd[2];
	int	pid;

	if (!ft_built_in_first(cmd, cable))
		return (1);
	cmd->fd_in = -2;
	ft_first_redirection(cmd, cable);
	ft_open_pipe(cable, fd);
	ft_forking(cable, &pid);
	if (cable->cmd->cmd[0])
	{
		if (!ft_strncmp(cable->cmd->cmd[0], "./minishell", \
				ft_strlen("./minishell")))
			g_var += 4;
	}
	if (!pid)
		ft_child(cmd, fd, cable);
	else
		ft_parent(cable, cmd, fd);
	return (0);
}
