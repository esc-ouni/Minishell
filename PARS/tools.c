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

void	check_type(t_list	*node)
{
	if (!ft_strncmp(node->cmd, "|", 1))
		node->type = PIPE;
	else if (!ft_strncmp(node->cmd, ";", 1))
		node->type = SMCL;
	else if (!ft_strncmp(node->cmd, ">", 1))
		node->type = REDR;
}

t_list	*ft_lstnew(char *s)
{
	t_list	*new_node;
	int		d;

	d = ft_strlen(s);
	new_node = NULL;
	new_node = (t_list *)malloc(sizeof(t_list) + 1);
	new_node->cmd = malloc(d + 1);
	if (new_node)
	{
		ft_memcpy(new_node->cmd, s, d + 1);
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
    printf("\nBig_shell >> ");
    printf("\x1B[0m");
}

void    start()
{
    char    *s;
    int     fd;

    fd = open("header.h", O_RDONLY);
    printf("\x1B[32m");
    while ((s = get_next_line(fd)))
	{
        printf("%s", s);
		free(s);
	}
    printf("\x1B[0m");
    printf("\n\n");
    close(fd);
}

void    after_parse(t_list  *head)
{
    t_list  *node;
    int i = 1;

    node = head;
    printf("\n");
    while(node)
    {
        printf("=> node %d;\n", i);
        printf("   command : %s\n", node->cmd);
        printf("   type    : %d", node->type);
        printf("\n\n");
        i++;
        node = node->next;
    }
	ft_lstclear(&head);
}

t_list  *read_line()
{
	int		i = 0;
    char    *s;
    char    **str;
	t_list	*head;

	head = NULL;
    s = readline("");
	str = ft_split(s, ' ');
	while (str[i])
	{
		ft_lstadd_back(&head, ft_lstnew(str[i]));
		free(str[i]);
		i++;
	}
	free(str[i]);
	free(str);
	free(s);
	return (head);
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