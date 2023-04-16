/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 04:40:47 by idouni            #+#    #+#             */
/*   Updated: 2023/04/03 04:41:04 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	ft_lstsize(t_list *lst)
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

void	ft_lstdelone(t_list *head,t_list *lst)
{
	t_list	*node;

	node = head;
	while (node->next && node->next->next)
	{
		if (node->next == lst)
		{
			node->next = node->next->next;
			free(node);
			return ;
		}
		node = node->next;
	}
	return ;
}

t_list	*ft_lstnew(char *s)
{
	t_list	*new_node;
	int		d;

	d = ft_strlen(s);
	new_node = NULL;
	new_node = (t_list *)malloc(sizeof(t_list));
	new_node->cmd = malloc(d + 1);
	if (new_node)
	{
		ft_memcpy(new_node->cmd, s, d + 1);
		new_node->cmd[d] = '\0';
		check_type(new_node);
		new_node->next = NULL;
	}
	return (new_node);
}

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*node;

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

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*o_last;

	if (*lst == NULL)
	{
		*lst = new;
		new->next = NULL;
		return ;
	}
	o_last = ft_lstlast(*lst);
	o_last->next = new;
	new->next = NULL;
}

void	ft_lstclear(t_list **lst)
{
	t_list	*node;
	t_list	*n_node;

	if (!lst)
		return ;
	node = *lst;
	while (node)
	{
		n_node = node->next;
		free(node->cmd);
		free(node);
		node = n_node;
	}
	*lst = NULL;
}