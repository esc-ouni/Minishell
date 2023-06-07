/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_exp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 11:32:29 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/07 14:13:03 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_replace_in_exp(t_struct *cable, t_exp **exist, char *str)
{
	(*exist)->str = ft_mstrdup(cable, str, NTMP);
}

void	ft_export_exp(t_struct *cable, char *str)
{
	char	*expstr;
	t_exp	*exist;

	expstr = ft_exported_str(str, cable);
	exist = ft_var_exp_exist(cable->exp, expstr);
	if (exist && ft_strchr(str, '='))
		ft_replace_in_exp(cable, &exist, expstr);
	else if (!exist)
		ft_exp_add_back(&cable->exp, ft_exp_new_node(expstr, cable));
	ft_alpha_order(cable);
}
