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

void	ft_lstdelone(t_list *lst, t_list **head)
{
	int	i = 0;
	t_list	*node;

	node = *head;
	if (node == lst)
	{
		*head = lst->next;
		free(lst);
		return ;
	}
	while (node->next)
	{
		if (node->next == lst)
		{
			node->next = node->next->next;
			free(lst);
			return ;
		}
		node = node->next;
	}
	// if (node->next == lst)
	// {
	// 	node->next = NULL;
	// 	free(lst);
	// 	return ;
	// }
}

t_list	*ft_lstnew(char *s)
{
	t_list	*new_node;
	int		d;

	d = ft_strlen(s);
	new_node = NULL;
	new_node = (t_list *)malloc(sizeof(t_list));
	if (new_node)
	{
		new_node->cmd = ft_strdup(s);
		new_node->next = NULL;
	}
	return (new_node);
}

t_list	*ft_lstlast(t_list *lst)
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

t_file	*ft_filenew(char *s)
{
	t_file	*new_file;

	new_file = NULL;
	new_file = (t_file *)malloc(sizeof(t_file));
	if (new_file)
	{
		new_file->filename = ft_strdup(s);
		new_file->next = NULL;
	}
	return (new_file);
}

void	ft_fileadd_back(t_file **lst, t_file *new)
{
	t_file *n;

	if (*lst == NULL)
	{
		*lst = new;
		new->next = NULL;
		return ;
	}
	while (n->next)
		n = n->next;
	n->next = new;
	new->next = NULL;
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

void	debug(void)
{
	printf("\x1B[32m");
	printf("\nDEBUG OK\n");
	printf("\x1B[0m");
}        

// void	add_file(t_file **st_file, char *s)
// {
// 	t_file	*new_file;

// 	printf("%s\n", s);
// 	new_file = malloc(sizeof(t_file));
// 	if (new_file)
// 	{
// 		new_file->filename = ft_strdup(s);
// 		new_file->next = NULL;
// 	}
// 	if (!st_file)
// 		*st_file = new_file;
// 	else
// 	{
// 		while ((*st_file)->next)
// 			*st_file = (*st_file)->next;
// 		(*st_file)->next = new_file;
// 	}
// }

