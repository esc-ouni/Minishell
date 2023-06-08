/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exp_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:49:09 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/08 16:34:42 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isplus(char *str, t_struct *cable)
{
	char	**eq;

	eq = ft_soft_split(str, '=', cable);
	if (strchr(eq[0], '+'))
		return (1);
	return (0);
}

void	ft_joint_to_export(t_struct *cable, char **str)
{
	t_envlst	*exist;
	char		**spl;

	*str = ft_trim_char(*str, '+', cable);
	exist = ft_var_env_exist(cable->envlst, *str, cable);
	if (exist)
	{
		spl = ft_soft_split(*str, '=', cable);
		*str = ft_mstrjoin(cable, exist->str, spl[1], NTMP);
	}
}
