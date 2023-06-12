/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 23:13:42 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/12 10:18:27 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_dup(t_struct *cable)
{
	cable->tmp_fd_in = dup(0);
	cable->tmp_fd_out = dup(1);
	// cable->tmp_err = dup(2);
	if (cable->tmp_fd_in < 0 || cable->tmp_fd_out < 0)
		ft_collectorclear(cable->collector, ALL);
}

void	ft_set_shlvl(t_struct *cable)
{
	char		*shlvl;
	char		*shld;
	char		**spl;
	t_envlst	*exist;
	t_envlst	*shild;
	int			lvl;
	int			t;

	exist = ft_var_env_exist(cable->envlst, "SHLVL", cable);
	shild = ft_var_env_exist(cable->envlst, "SHILD", cable);
	if (!shild)
	{
		shlvl = ft_mstrjoin(cable, "SHLVL=", "0", NTMP);
		ft_export(cable, shlvl);
		shld = ft_mstrjoin(cable, "SHILD=", "1", NTMP);
		ft_export(cable, shld);
		return ;
	}
	if (!exist)
	{
		shlvl = ft_mstrjoin(cable, "SHLVL=", "1", NTMP);
		ft_export(cable, shlvl);
		return ;
	}
	spl = ft_msoft_split_include(exist->str, '=', cable);
	lvl = ft_atoi(spl[1]);
	if (lvl < 0)
		lvl = -1;
	lvl++;
	if (lvl > 999)
		lvl = 0;
	t = cable->exit_val;
	cable->exit_val = lvl;
	shlvl = ft_mstrjoin(cable, "SHLVL=", ft_mitoa(cable), NTMP);
	cable->exit_val = t;
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
	// after_parse2(cable->cmd);
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
