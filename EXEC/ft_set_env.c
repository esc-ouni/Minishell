/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 11:18:04 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/08 13:48:27 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_set_min_ev(t_struct *cable)
{
	ft_env_add_back(&cable->envlst, \
		ft_env_new_node("PWD=/Users/msamhaou/Desktop/Minishell", cable));
	ft_env_add_back(&cable->envlst, ft_env_new_node("_=/usr/bin/env", cable));
}

void	ft_set_env_lst(t_struct *cable, char **ev)
{
	int	i;

	i = 0;
	cable->envlst = NULL;
	if (ev[i])
	{
		while (ev[i])
			ft_env_add_back(&cable->envlst, ft_env_new_node(ev[i++], cable));
	}
	else
		ft_set_min_ev(cable);
}

void	ft_env_set(t_struct *cable)
{
	t_envlst	*envlst;
	size_t		size;
	int			i;

	envlst = cable->envlst;
	size = ft_envlst_size(envlst);
	cable->env = (char **)h_malloc(cable->collector, (sizeof(char *) * (size + 1)), cable->env, TMP);
	i = 0;
	while (envlst)
	{
		cable->env[i++] = ft_mstrdup(cable, envlst->str, TMP);
		envlst = envlst->next;
	}
	cable->env[i] = NULL;
}
