/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:36:07 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/09 17:14:33 by msamhaou         ###   ########.fr       */
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

void	ft_macrofy(t_struct *cable)
{
	if (cable->exit_val != 1)
		cable->exit_val = WEXITSTATUS(cable->exit_val);
}

void	ft_exec(t_struct *cable)
{
	t_cmd	*cmd;

	cmd = cable->cmd;
	ft_set_path(cmd, cable);
	cable->cmd_numb = ft_cmd_count(cmd);
	while (cmd)
	{
		ft_fork(cmd, cable);
		cmd = cmd->next;
	}
	while (wait(&cable->exit_val) != -1)
		;
	ft_macrofy(cable);
}
