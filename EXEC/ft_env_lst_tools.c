/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_lst_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 11:16:54 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/02 11:17:09 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envlst	*ft_env_new_node(char *str)
{
	t_envlst	*node;

	node = (t_envlst *)malloc(sizeof(t_envlst));
	node->str = ft_strdup(str);
	node->next = NULL;
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

