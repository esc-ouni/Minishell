/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:43:54 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/08 14:21:44 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_parent(t_cmd *cmd, int *fd, t_struct *cable)
{
	char	*line;

	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	if (cmd->fd_in)
		close(cmd->fd_in);
	close (fd[0]);
	return (0);
}

static int	ft_open_in_file(t_cmd *cmd, t_struct *cable)
{
	t_file	*files;
	int		is_here;

	files = cmd->in_files;
	cmd->fd_in = -1;
	while (files)
	{
		is_here = 0;
		if (files->o_flag == O_APPEND)
		{
			is_here = 1;
			ft_heredoc_proc(files, cable);
		}
		else if (files->o_flag == O_TRUNC)
			cmd->fd_in = open(files->filename, O_RDONLY);
		if (cmd->fd_in < 0 && !is_here)
			return (perror(files->filename), -1);
		if (!is_here)
			dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
		files = files->next;
	}
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
	else if (cmd->builtflag == EXT)
		ft_quit(NOT, cable);
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
		return (0);
	if (ft_first_redirection(cmd, cable) < 0)
		return (1);
	pipe(fd);
	cmd->pipe_fd = fd;
	pid = fork();
	if (cable->cmd->cmd[0])
	{
		if (!ft_strncmp(cable->cmd->cmd[0], "./minishell", \
				ft_strlen("./minishell")))
		g_var += 4;
	}
	if (!pid)
		ft_child(cmd, fd, cable);
	else
		ft_parent(cmd, fd, cable);
	return (0);
}
