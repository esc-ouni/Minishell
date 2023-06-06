/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 11:33:20 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/06 11:33:44 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_replace_in_envlst(t_struct *cable, t_envlst **exist, char *str)
{
	(*exist)->str = ft_mstrdup(cable, str, NTMP);
}

void	ft_export_env(t_struct *cable, char	*str)
{
	t_envlst	*exist;

	exist = ft_var_env_exist(cable->envlst, str);
	if (exist)
		ft_replace_in_envlst(cable, &exist, str);
	else
		ft_env_add_back(&cable->envlst, ft_env_new_node(str, cable));
}
