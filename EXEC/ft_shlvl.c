/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shlvl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 13:24:51 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/12 13:35:13 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_set_shild(t_struct *cable)
{
	t_envlst	*shild;

	shild = ft_var_env_exist(cable->envlst, "SHILD", cable);
	if (!shild)
	{
		ft_export(cable, "SHLVL=1");
		ft_export(cable, "SHILD=1");
		return (1);
	}
	return (0);
}

static int	ft_add_lvl(t_struct *cable, t_envlst *exist)
{
	int		lvl;
	char	**spl;
	int		t;
	char	*shlvl;

	spl = ft_msoft_split_include(exist->str, '=', cable);
	lvl = ft_atoi(spl[1]);
	if (lvl < 0)
		lvl = -1;
	lvl++;
	if (lvl > 999)
	{
		ft_unset(cable, "SHLVL");
		return (0);
	}
	t = cable->exit_val;
	cable->exit_val = lvl;
	shlvl = ft_mstrjoin(cable, "SHLVL=", ft_mitoa(cable), NTMP);
	cable->exit_val = t;
	ft_export(cable, shlvl);
	return (0);
}

void	ft_set_shlvl(t_struct *cable)
{
	t_envlst	*exist;

	exist = ft_var_env_exist(cable->envlst, "SHLVL", cable);
	if (ft_set_shild(cable) == 1)
		return ;
	if (!exist)
		ft_export(cable, "SHLVL=1");
	else
		ft_add_lvl(cable, exist);
}
