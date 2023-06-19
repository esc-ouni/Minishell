/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:36:07 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/19 21:25:02 by msamhaou         ###   ########.fr       */
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
	if (!cable->cmd)
		return ;
	if (cable->exit_val != 1)
		cable->exit_val = WEXITSTATUS(cable->exit_val);
}

void	ft_exec(t_struct *cable)
{
	t_cmd	*cmd;

	if (!cable->cmd)
		return ;
	cmd = cable->cmd;
	g_var = 0;
	ft_set_path(cmd, cable);
	cable->cmd_numb = ft_cmd_count(cmd);
	while (cmd)
	{
		ft_fork(cmd, cable);
		cmd = cmd->next;
	}
	waitpid(cable->last_pid, &cable->exit_val, 0);
	while (wait(NULL) != -1)
		;
	ft_macrofy(cable);
	printf("%d\n", cable->exit_val);
	get_sig_exitval(cable, g_var);
}

int	ft_forking(t_struct *cable, int *pid)
{
	*pid = fork();
	if (*pid == -1)
		return (perror("fork"), ft_close_fdtmp(cable), \
			ft_collectorclear(cable->collector, ALL), -1);
	return (0);
}
