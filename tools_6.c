/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:30:30 by idouni            #+#    #+#             */
/*   Updated: 2023/05/22 16:35:23 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

char	**allocate_full_cmd(t_collector **collector, char **full_cmd)
{
	char	**str;
	int		i;

	i = 0;
	str = NULL;
	if (full_cmd)
	{
		while (full_cmd[i])
			i++;
		str = h_malloc(collector, sizeof(char *) * (i + 1), str);
		i = 0;
		while (full_cmd[i])
		{
			str[i] = ft_mstrdup(collector, full_cmd[i]);
			i++;
		}
		str[i] = NULL;
	}
	else
	{
		str = h_malloc(collector, sizeof(char *), str);
		str[0] = NULL;
	}
	return (str);
}

t_file	*allocate_out_files(t_collector **collector, t_file *out_files)
{
	t_file	*out_files2;

	out_files2 = NULL;
	while (out_files)
	{
		add_file_file(collector, &out_files2, out_files);
		out_files = out_files->next;
	}
	return (out_files2);
}

t_file	*allocate_in_files(t_collector **collector, t_file *in_files)
{
	t_file	*in_files2;

	in_files2 = NULL;
	while (in_files)
	{
		add_file_file(collector, &in_files2, in_files);
		in_files = in_files->next;
	}
	return (in_files2);
}

void	add_to_cmd(t_collector **collector, t_cmd **head, char **full_cmd, \
t_files *files)
{
	t_cmd	*new_cmd;
	t_cmd	*tmp;

	new_cmd = NULL;
	new_cmd = h_malloc(collector, sizeof(t_cmd), new_cmd);
	new_cmd->cmd = allocate_full_cmd(collector, full_cmd);
	new_cmd->out_files = allocate_out_files(collector, files->out_files);
	new_cmd->in_files = allocate_in_files(collector, files->in_files);
	if (!(*head))
		*head = new_cmd;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_cmd;
	}
	new_cmd->next = NULL;
}

int	check_syntax2(t_lexer **h_lexer)
{
	t_lexer	*node;

	node = *h_lexer;
	while (node)
	{
		if (node->type == WH_SP)
			node = node->next;
		else if ((node->type == R_OA) || (node->type == R_OT) || \
		(node->type == R_IN) || (node->type == R_HD))
		{
			node = node->next;
			while (node && node->type == WH_SP)
				node = node->next;
			if ((node) && ((node->type == R_OA) || (node->type == R_OT) || \
			(node->type == R_IN) || (node->type == R_HD || node->type == PIP)))
				return (syntx_err(), 1);
			else if (!node)
				return (syntx_err(), 1);
			node = node->next;
		}
		else
			node = node->next;
	}
	return (0);
}
