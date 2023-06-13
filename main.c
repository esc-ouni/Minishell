/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 23:13:42 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/13 21:33:29 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_dup(t_struct *cable)
{
	cable->tmp_fd_in = dup(0);
	cable->tmp_fd_out = dup(1);
	cable->tmp_err = dup(2);
	if (cable->tmp_fd_in < 0 || cable->tmp_err < 0)
	{
		perror("");
		ft_collectorclear(cable->collector, ALL);
	}
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
	ft_set_shlvl(cable);
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
	if (dup2(cable->tmp_fd_in, 0) == -1 || dup2(cable->tmp_err, 2) == -1)
		return (perror(""), ft_collectorclear(cable->collector, ALL));
	cable->cmd = get_cmd(cable);
	// after_parse2(cable->cmd);
	ft_exec(cable);
	ft_collectorclear(cable->collector, TMP);
}

int	main(int ac, char **av, char **ev)
{
	t_struct	*cable;

	prm(ac, av, ev);
	ft_init(ev, &cable);
	strt(cable);
	while (1)
	{
		g_var = 1;
		program(cable);
	}
}
