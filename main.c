/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:42:08 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/11 23:09:24 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_dup(t_struct *cable)
{
	cable->tmp_fd_in = dup(0);
	cable->tmp_fd_out = dup(1);
	cable->tmp_err = dup(2);
	if (cable->tmp_fd_in < 0 || cable->tmp_fd_out < 0)
		ft_collectorclear(cable->collector, ALL);
}

void	ft_set_shlvl(t_struct *cable)
{
	char		*shlvl;
	char		**spl;
	t_envlst	*exist;
	int			lvl;

	exist = ft_var_env_exist(cable->envlst, "SHLVL", cable);
	spl = ft_msoft_split_include(exist->str, '=', cable);
	lvl = ft_atoi(spl[1]);
	lvl++;
	shlvl = ft_mstrjoin(cable, "SHLVL=", ft_itoa(lvl), NTMP);
	ft_export(cable, shlvl);
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
	if (dup2(cable->tmp_fd_in, 0) == -1)
		return (perror(""), ft_collectorclear(cable->collector, ALL));
	cable->cmd = get_cmd(cable);
	ft_exec(cable);
	get_sig_exitval(cable, g_var);
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
