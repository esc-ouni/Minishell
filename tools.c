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

t_list	*ft_lstnew(char *s)
{
	t_list	*new_node;

	new_node = NULL;
	new_node = (t_list *)malloc(sizeof(t_list));
	// new_node = (t_list *)h_malloc(data, sizeof(t_list), new_node);
	if (new_node)
	{
        ft_memcpy(new_node->cmd, s, ft_strlen(s));
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

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst == NULL || new == NULL)
		return ;
	new->next = *lst;
	*lst = new;
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*o_last;

	if (lst == NULL || new == NULL)
		return ;
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
		free(node);
		node = n_node;
	}
	*lst = NULL;
}

void    prompt()
{
    printf("\x1B[34m");
    printf("Your_prompt >> ");
    printf("\x1B[0m");
}

void    start()
{
    char    *s;
    int     fd;

    fd = open("header.h", O_RDONLY);
    printf("\x1B[32m");
    while ((s = get_next_line(fd)))
        printf("%s", s);
    printf("\x1B[0m");
    printf("\n\n");
    close(fd);
}

void    after_parse(t_list  **head)
{
    t_list  *node;
    int i = 0;

    node = *head;
    while(node)
    {
        printf("node %d\n", i);
        printf("command   : %s", node->cmd);
        printf("tar. file : %s", node->target);
        printf("\n\n");
        i++;
        node = node->next;
    }
}

// void	*h_malloc(t_data data, size_t s, void *p)
// {
// 	p = malloc(s);
// 	if (!p)
// 	{
// 		ft_exit_with_error(data);
// 	}
// 	return (p);
// }