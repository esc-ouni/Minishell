/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:33:34 by idouni            #+#    #+#             */
/*   Updated: 2023/05/22 17:45:16 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_mlstsize(t_mlist *lst)
{
	size_t	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

int	ft_cmdsize(t_cmd *cmd)
{
	size_t	i;
	t_cmd	*n_cmd;

	i = 0;
	n_cmd = cmd;
	while (n_cmd)
	{
		n_cmd = n_cmd->next;
		i++;
	}
	return (i);
}

t_mlist	*ft_mlstnew(t_collector **collector, char *s)
{
	t_mlist	*new_node;

	new_node = NULL;
	new_node = h_malloc(collector, sizeof(t_mlist), new_node);
	if (new_node)
	{
		new_node->cmd = ft_mstrdup(collector, s);
		new_node->next = NULL;
	}
	return (new_node);
}

t_mlist	*ft_mlstlast(t_mlist *lst)
{
	void	*node;

	if (lst == NULL)
		return (NULL);
	node = lst;
	while (lst != NULL)
	{
		node = lst;
		lst = lst->next;
	}
	return (node);
}

void	ft_mlstadd_back(t_mlist **lst, t_mlist *new)
{
	t_mlist	*o_last;

	if (*lst == NULL)
	{
		*lst = new;
		new->next = NULL;
		return ;
	}
	o_last = ft_mlstlast(*lst);
	o_last->next = new;
	new->next = NULL;
}
