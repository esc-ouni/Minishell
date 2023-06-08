/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:36:07 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/08 11:47:16 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cmd_count(t_cmd *cmd)
{
	int	i;

	i = 0;
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
		wait(&cable->exit_val);
}
