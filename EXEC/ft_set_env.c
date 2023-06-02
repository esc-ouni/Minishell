/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 11:18:04 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/02 11:18:33 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_env_lst(t_struct *cable, char **ev)
{
	int	i;

	i = 0;
	cable->envlst = NULL;
	while (ev[i])
		ft_env_add_back(&cable->envlst, ft_env_new_node(ev[i++]));
}

void	ft_env_set(t_struct *cable, char **ev)
{
	ft_set_env_lst(cable, ev);
}

