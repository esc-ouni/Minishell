/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset_exp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 11:38:13 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/08 16:16:10 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_skip_exp_node(t_struct *cable, t_exp *exist)
{
	t_exp	*exp;

	exp = cable->exp;
	if (cable->exp == exist)
		cable->exp = cable->exp->next;
	else
	{
		while (exp->next != exist)
			exp = exp->next;
		exp->next = exp->next->next;
	}
}

void	ft_unset_exp(t_struct *cable, char *str)
{
	t_exp	*exist;
	char	*decl;

	decl = ft_mstrjoin(cable, "declare -x ", str, TMP);
	exist = ft_var_exp_exist(cable->exp, decl, cable);
	if (exist)
		ft_skip_exp_node(cable, exist);
}
