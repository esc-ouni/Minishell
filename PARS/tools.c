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

void add_file_node(t_file **head, char *filename, int flag)
{
    t_file *tmp;
    t_file *new_node = malloc(sizeof(t_file));
    
    new_node->filename = ft_strdup(filename);
    new_node->o_flags = flag;
    
    if (!(*head))
    {
        *head = new_node;
        new_node->next = NULL;
    }
    else
    {
        tmp = *head;
        while (tmp->next)
        {
            tmp = tmp->next;
        }
        tmp->next = new_node;
        new_node->next = NULL;
    }
}

void	add_file_file(t_file **head, t_file *file)
{
    t_file *tmp;
    t_file *new_node = malloc(sizeof(t_file));
    
    new_node->filename = ft_strdup(file->filename);
    new_node->o_flags = file->o_flags;
    
    if (!(*head))
    {
        *head = new_node;
        new_node->next = NULL;
    }
    else
    {
        tmp = *head;
        while (tmp->next)
        {
            tmp = tmp->next;
        }
        tmp->next = new_node;
        new_node->next = NULL;
    }
}

void add_to_cmd(t_cmd **head, char **full_cmd, t_file *out_files, t_file *in_files)
{
	t_file	*out_files2;
	t_file	*in_files2;

	t_cmd	*tmp;
	t_cmd *new_cmd = malloc(sizeof(t_cmd));

	out_files2 = NULL;
	in_files2 = NULL;

	char **str = malloc(sizeof(char *) * 15);
	char **s = str;
	// s = NULL;
	while (*full_cmd)
	{
		*s = ft_strdup(*full_cmd);
		// printf("%s ", *s);
		full_cmd++;
		s++;
	}
	*s = NULL;

	while (out_files)
	{
		add_file_file(&out_files2, out_files);
		out_files = out_files->next;
	}

	while (in_files)
	{
		add_file_file(&in_files2, in_files);
		in_files = in_files->next;
	}

	new_cmd->cmd = str;
	new_cmd->out_files = out_files2;
	new_cmd->in_files = in_files2;

	// printf("hello %d\n",sizeof(full_cmd));
	if (!(*head))
    {
        *head = new_cmd;
        new_cmd->next = NULL;
    }
    else
    {
        tmp = *head;
        while (tmp->next)
        {
            tmp = tmp->next;
        }
        tmp->next = new_cmd;
        new_cmd->next = NULL;
    }
}

void	add_lexer(t_lexer **head, char *content)
{
	t_lexer	*tmp;
	t_lexer	*new_node;

	new_node = malloc(sizeof(t_lexer));
	new_node->cmd = ft_strdup(content);

	if (!(*head))
	{
		*head = new_node;
		new_node->next = NULL;
	}
	else
	{
		tmp = *head;
		while (tmp->next)
		{
			tmp = tmp->next;
		}
		tmp->next = new_node;
		new_node->next = NULL;
	}
}
