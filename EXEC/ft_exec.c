/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:36:07 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/06 17:02:01 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int	ft_parent(t_cmd *cmd, t_struct *cable)
{
	char	*line;

	close(cmd->pipe_fd[1]);
	dup2(cmd->pipe_fd[0], STDIN_FILENO);
	if (cmd->fd_in)
		close(cmd->fd_in);
	close (cmd->pipe_fd[0]);
	return (0);
}

int	ft_open_in_file(t_cmd *cmd, t_struct *cable)
{
	t_file	*files;

	files = cmd->in_files;
	while (files)
	{
		cmd->fd_in = open(files->filename, O_RDONLY);
		if (files->o_flag == O_APPEND)
			ft_heredoc(cmd, files->filename);
		if (cmd->fd_in < 0)
			return (perror(""), 1);
		files = files->next;
	}
	return (0);
}

int	ft_built_in_first(t_cmd *cmd, t_struct *cable)
{
	int i = 0;

	if (cable->cmd_numb > 1)
		return (1);
	if (cmd->builtflag == CD)
	{
		ft_cd(cmd);
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

void	ft_first_redirection(t_cmd *cmd, t_struct *cable)
{
	if (cmd->in_files)
	{
		ft_open_in_file(cmd, cable);
		dup2(cmd->fd_in, STDIN_FILENO);
	}
}

int	ft_fork(t_cmd *cmd, t_struct *cable)
{
	int	fd[2];
	int	pid;

	if (!ft_built_in_first(cmd, cable))
		return (0);
	ft_first_redirection(cmd, cable);
	pipe(fd);
	cmd->pipe_fd = fd;
	pid = fork();
	if (!pid)
		ft_child(cmd, cable);
	else
		ft_parent(cmd, cable);
	//cable err;
	return (0);
}

int	ft_cmd_count(t_cmd *cmd)
{
	int	i = 0;

	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}

void	ft_exec(t_struct *cable)
{
	t_cmd	*cmd;
	int		numl;

	cmd = cable->cmd;
	ft_set_path(cmd, cable);
	cable->cmd_numb = ft_cmd_count(cmd);
	while (cmd)
	{
		ft_fork(cmd, cable);
		cmd = cmd->next;
	}
	while (cable->cmd_numb--)
		wait(NULL);
}
