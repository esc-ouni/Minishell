/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:42:08 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/08 16:34:23 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_dup(t_struct *cable)
{
	cable->tmp_fd_in = dup(0);
	cable->tmp_fd_out = dup(1);
	if (cable->tmp_fd_in < 0 || cable->tmp_fd_out < 0)
		ft_collectorclear(cable->collector, ALL);
}

void	ft_init(char **ev, t_struct **cab)
{
	t_struct			*cable;
	static t_collector	*collector;

	collector = NULL;
	cable = NULL;
	cable = h_malloc(&collector, sizeof(t_struct), cable, NTMP);
	cable->collector = &collector;
	ft_set_env_lst(cable, ev);
	ft_exp_set(cable);
	ft_unset(cable, "OLDPWD");
	ft_export_exp(cable, "OLDPWD");
	ft_dup(cable);
	cable->cmd = NULL;
	cable->exit_val = 0;
	cable->is_heredoc = 0;
	cable->cmd_numb = 0;
	*cab = cable;
}

void	program(t_struct *cable)
{
	ft_env_set(cable);
	if (dup2(cable->tmp_fd_in, 0) < 0)
		ft_collectorclear(cable->collector, ALL);
	cable->cmd = get_cmd(cable);
	g_var = 0;
	ft_exec(cable);
	g_var = 1;
	ft_collectorclear(cable->collector, TMP);
}

int	main(int ac, char **av, char **ev)
{
	t_struct	*cable;

	g_var = 1;
	prm(ac, av, ev);
	ft_init(ev, &cable);
	strt(cable);
	while (1)
		program(cable);
}
