/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 11:18:04 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/05 16:15:47 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_env_lst(t_struct *cable, char **ev)
{
	int	i;

	i = 0;
	cable->envlst = NULL;
	while (ev[i])
		ft_env_add_back(&cable->envlst, ft_env_new_node(ev[i++], cable));
}

void	ft_env_set(t_struct *cable)
{
	t_envlst	*envlst;
	size_t		size;
	int			i;

	envlst = cable->envlst;
	size = ft_envlst_size(envlst);
	cable->env = (char **)h_malloc(cable->collector,sizeof(char *) * (size + 1), cable->env, NTMP);
	i = 0;
	while (envlst)
	{
		cable->env[i++] = ft_mstrdup(cable, envlst->str);
		envlst = envlst->next;
	}
	cable->env[i] = NULL;
}

