/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset_envlst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 11:37:04 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/07 11:43:34 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_skip_env_node(t_struct *cable, t_envlst *exist)
{
	t_envlst	*envlst;

	envlst = cable->envlst;
	if (cable->envlst == exist)
		cable->envlst = cable->envlst->next;
	else
	{
		while (envlst->next != exist)
			envlst = envlst->next;
		envlst->next = envlst->next->next;
	}
}


void	ft_unset_envlst(t_struct *cable, char *str)
{
	t_envlst	*exist;

	exist = ft_var_env_exist(cable->envlst, str);
	if (exist)
		ft_skip_env_node(cable, exist);
}
