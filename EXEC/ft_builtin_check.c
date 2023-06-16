/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 13:23:20 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/16 13:28:49 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_built_in_first(t_cmd *cmd, t_struct *cable)
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
