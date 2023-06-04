/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 15:02:48 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/04 10:03:04 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_child(t_cmd *cmd, t_struct *cable)
{

}

void	ft_parent(t_cmd *cmd, t_struct *cable)
{
	
}

void	ft_first_redirection(t_cmd *cmd, t_struct *cable)
{
	if (cmd->in_file)
		ft_open_files();
}

void	ft_fork(t_cmd *cmd, t_struct *cable)
{
	int	fd[2];
	int	pid;

	ft_first_redirection(cmd, cable);
	pipe(fd);
	pid = fork();
	if (!pid)
		ft_child(cmd, cable);
	else
		ft_parent(cmd, cable);
}

void	ft_exec(t_struct *cable)
{
	t_cmd	*cmd;

	cmd = cable->cmd;
	while (cmd)
	{
		ft_fork(cmd, cable);
		cmd = cmd->next;
	}
}
