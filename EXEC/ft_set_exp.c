/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_exp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 11:46:21 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/02 11:50:41 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_exp(t_struct *cable, char **ev)
{
	int	i;

	i = 0;
	cable->envlst = NULL;
	while (ev[i])
		ft_exp_add_back(&cable->envlst, ft_exp_new_node(ev[i++]));
}

void	ft_env_set(t_struct *cable, char **ev)
{
	ft_set_exp(cable, ev);
}
