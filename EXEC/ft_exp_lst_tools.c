/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exp_lst_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 11:46:53 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/03 14:51:37 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exp	*ft_exp_new_node(char *str)
{
	t_exp	*node;

	node = (t_exp *)malloc(sizeof(t_exp));
	node->str = ft_strdup(str);
	node->next = NULL;
	return (node);
}

t_exp	*ft_last_explst(t_exp *envlst)
{
	while (envlst->next)
		envlst = envlst->next;
	return (envlst);
}

void	ft_exp_add_back(t_exp **envlst, t_exp *toadd)
{
	if (!*envlst)
		*envlst = toadd;
	else
		ft_last_explst(*envlst)->next = toadd;
}
