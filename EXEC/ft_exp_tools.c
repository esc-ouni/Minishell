/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exp_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:49:09 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/08 11:50:00 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isplus(char *str)
{
	char	**eq;

	eq = ft_soft_split(str, '=');
	if (strchr(eq[0], '+'))
		return (ft_free_stringp(eq), 1);
	return (ft_free_stringp(eq), 0);
}

void	ft_joint_to_export(t_struct *cable, char **str)
{
	t_envlst	*exist;
	char		**spl;

	*str = ft_trim_char(*str, '+', cable);
	exist = ft_var_env_exist(cable->envlst, *str);
	if (exist)
	{
		spl = ft_soft_split(*str, '=');
		*str = ft_mstrjoin(cable, exist->str, spl[1], NTMP);
		ft_free_stringp(spl);
	}
}
