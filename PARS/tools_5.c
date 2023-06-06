/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:23:36 by idouni            #+#    #+#             */
/*   Updated: 2023/06/06 15:22:21 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_mlstclear(t_mlist **lst)
{
	t_mlist	*node;
	t_mlist	*n_node;

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

void	add_file_node(t_struct *cable, t_file **head, \
char *filename, int flag)
{
	t_file	*tmp;
	t_file	*new_node;

	new_node = NULL;
	new_node = h_malloc(cable->collector, sizeof(t_file), new_node, TMP);
	new_node->filename = ft_mstrdup(cable, filename, TMP);
	new_node->o_flag = flag;
	if (!(*head))
	{
		*head = new_node;
		new_node->next = NULL;
	}
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
		new_node->next = NULL;
	}
}

void	add_file_file(t_struct *cable, t_file **head, t_file *file)
{
	t_file	*tmp;
	t_file	*new_node;

	new_node = NULL;
	new_node = h_malloc(cable->collector, sizeof(t_file), new_node, TMP);
	new_node->filename = ft_mstrdup(cable, file->filename, TMP);
	new_node->o_flag = file->o_flag;
	if (!(*head))
	{
		*head = new_node;
		new_node->next = NULL;
	}
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
		new_node->next = NULL;
	}
}

void	add_to_fullcmd_st(t_struct *cable, char ***full_cmd, t_lexer *n)
{
	int		l;
	t_lexer	*tmp;

	l = 0;
	tmp = n;
	while (tmp && tmp->type != PIP)
	{
		l++;
		tmp = tmp->next;
	}
	(*full_cmd) = h_malloc(cable->collector, sizeof(char *) * \
	(l + 1), *full_cmd, TMP);
	(*full_cmd)[0] = ft_mstrdup(cable, n->cmd, TMP);
	(*full_cmd)[1] = NULL;
}

void	add_to_fullcmd(t_struct *cable, char ***full_cmd, \
t_lexer *n, int j)
{
	int	l;

	l = 0;
	if (!((*full_cmd)))
		return (add_to_fullcmd_st(cable, full_cmd, n));
	else
	{
		while ((*full_cmd)[l])
			l++;
		if (j && l)
		{
			l--;
			(*full_cmd)[l] = ft_mstrjoin(cable, (*full_cmd)[l], n->cmd, TMP);
			(*full_cmd)[l + 1] = NULL;
			return ;
		}
		else
		{
			(*full_cmd)[l] = ft_mstrdup(cable, n->cmd, TMP);
			(*full_cmd)[l + 1] = NULL;
			return ;
		}
	}
}
