/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_lst_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 11:16:54 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/05 16:15:47 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_envlst_size(t_envlst *envlst)
{
	size_t	i;

	i = 0;
	while (envlst)
	{
		i++;
		envlst = envlst->next;
	}
	return (i);
}

t_envlst	*ft_env_new_node(char *str, t_struct *cable)
{
	t_envlst	*node;

	node = (t_envlst *)h_malloc(cable->collector ,sizeof(t_envlst), node, NTMP);
	node->str = ft_mstrdup(cable, str);
	node->next = NULL;
	return (node);
}

t_envlst	*ft_last_envlst(t_envlst *envlst)
{
	while (envlst->next)
		envlst = envlst->next;
	return (envlst);
}

void	ft_env_add_back(t_envlst **envlst, t_envlst *toadd)
{
	if (!*envlst)
		*envlst = toadd;
	else
		ft_last_envlst(*envlst)->next = toadd;
}

t_envlst	*ft_var_env_exist(t_envlst *envlst, char *str)
{
	char	**var;

	var = ft_soft_split(str, '=');
	while (envlst)
	{
		if (!ft_strcmp(envlst->str, var[0]))
			return (ft_free_stringp(var), envlst);
		envlst = envlst->next;
	}
	ft_free_stringp(var);
	return (NULL);
}
