/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 23:13:42 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/19 17:45:55 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_dup(t_struct *cable)
{
	cable->tmp_fd_in = dup(0);
	if (cable->tmp_fd_in < 0 || cable->tmp_err < 0)
	{
		perror("");
		ft_collectorclear(cable->collector, ALL);
	}
	cable->tmp_err = dup(2);
	if (cable->tmp_err < 0)
	{
		perror("");
		ft_close(cable, cable->tmp_fd_in);
		ft_collectorclear(cable->collector, ALL);
	}
}

void	ft_init(char **ev, t_struct **cab)
{
	t_struct			*cable;
	static t_collector	*collector;

	collector = NULL;
	cable = NULL;
	g_var = 1;
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
	cable->rd = 1;
	cable->cmd_numb = 0;
	*cab = cable;
}

void	program(t_struct *cable)
{
	ft_env_set(cable);
	if (dup2(cable->tmp_fd_in, 0) == -1 || dup2(cable->tmp_err, 2) == -1)
	{
		ft_close_fdtmp(cable);
		return (perror("dup2"), ft_collectorclear(cable->collector, ALL));
	}
	cable->cmd = get_cmd(cable);
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
		program(cable);
}
