/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taha <taha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:43:54 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/12 17:53:59 by taha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_parent(t_struct *cable, t_cmd *cmd, int *fd)
{
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		return (perror(""), ft_collectorclear(cable->collector, ALL), 1);
	if (cmd->fd_in)
		close(cmd->fd_in);
	close (fd[0]);
	return (0);
}

static int	ft_built_in_first(t_cmd *cmd, t_struct *cable)
{
	int	i;

	i = 1;
	if (cable->cmd_numb > 1)
		return (1);
	if (cmd->builtflag == CD)
	{
		ft_cd(cmd, cable);
		return (0);
	}
	else if (cmd->builtflag == EXT && cable->cmd_numb == 1)
		ft_quit(cmd);
	else if (cmd->builtflag == EXPT && cmd->cmd[1])
	{
		while (cmd->cmd[i])
			ft_export(cable, cmd->cmd[i++]);
		return (0);
	}
	else if (cmd->builtflag == UNST)
	{
		while (cmd->cmd[i])
			ft_unset(cable, cmd->cmd[i++]);
		return (0);
	}
	return (1);
}

static int	ft_first_redirection(t_cmd *cmd, t_struct *cable)
{
	int	op;

	op = 0;
	if (cmd->in_files)
	{
		op = ft_open_in_file(cmd, cable);
		if (op < 0)
			cable->exit_val = 1;
	}
	return (op);
}

int	ft_fork(t_cmd *cmd, t_struct *cable)
{
	int	fd[2];
	int	pid;

	if (!ft_built_in_first(cmd, cable))
		return (1);
	if (ft_first_redirection(cmd, cable) < 0)
		return (1);
	if (pipe(fd) == -1)
		return (perror(""), ft_collectorclear(cable->collector, ALL), -1);
	pid = fork();
	if (pid == -1)
		return (perror(""), ft_collectorclear(cable->collector, ALL), -1);
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
