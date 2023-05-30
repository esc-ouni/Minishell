/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 08:04:21 by msamhaou          #+#    #+#             */
/*   Updated: 2023/05/28 17:36:37 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_redirect_child(t_cmd *lol, int *fd)
{
	if (lol->out_files)
	{
		ft_open_out_files(lol);
		if (dup2(lol->cmd_fdout, STDOUT_FILENO) < 0)
			exit(1);
	}
	else
		if (dup2(fd[1], STDOUT_FILENO) < 0)
			exit(1);
	return (0);
}

int	ft_child(t_cmd *lol, int *fd, t_init *init)
{
	close(fd[0]);
	if (init->err_in)
		exit(1);
	ft_redirect_child(lol, fd);
	if (lol->builtflag)
	{
		ft_builtin(lol, init);
		exit (0);
	}
	else if (lol->builtflag == NOT)
	{
		if ((execve(lol->cmd_path, lol->cmd, init->myenv) < 0) \
			&& !lol->builtflag)
		{
			if (lol->cmd[0])
				ft_putendl_fd("cmd does not exist", 2);
			close(fd[1]);
			exit(1);
		}
		exit(0);
	}
	return (1);
}

int	ft_parent(t_cmd *lol, int *fd, int *pid)
{
	char	*line;

	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	if (lol->cmd_fdin)
		close(lol->cmd_fdin);
	if (lol->last_cmd)
	{
		line = get_next_line(fd[0]);
		while (line)
		{
			write(STDOUT_FILENO, line, ft_strlen(line));
			free(line);
			line = get_next_line(fd[0]);
		}
	}
	close (fd[0]);
	return (0);
}

int	ft_fork(t_cmd *lol, t_init *init)
{
	int	pid;
	int	fd[2];

	if (!ft_built_in_first(lol, init))
		return (0);
	if (lol->in_files)
	{
		init->err_in = ft_open_in_file(lol);
		dup2(lol->cmd_fdin, STDIN_FILENO);
	}
	pipe(fd);
	pid = fork();
	if (pid == 0)
		ft_child(lol, fd, init);
	else
		ft_parent(lol, fd, &pid);
	init->err_in = 0;
	return (0);
}
