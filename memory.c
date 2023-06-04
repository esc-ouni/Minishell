/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:20:18 by idouni            #+#    #+#             */
/*   Updated: 2023/06/04 18:27:37 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_collectorclear(t_collector **collector, t_flag flag)
{
	t_tmp	*node;
	t_tmp	*n_node;
	t_ntmp	*node1;
	t_ntmp	*n_node1;

	if (!(*collector) || !collector)
		return ;
	if (flag == TMP)
	{
		node = (*collector)->tmp_cltr;
		if (!node)
			return ;
		while (node)
		{
			n_node = node->next;
			if (node->tmp_addr)
			{
				printf("%p\n", node->tmp_addr);
				free(node->tmp_addr);
			}
			free(node);
			node = n_node;
		}
		(*collector)->tmp_cltr = NULL;
	}
	else if (flag == NTMP)
	{
		node1 = (*collector)->ntmp_cltr;
		if (!node1)
			return ;
		while (node1)
		{
			n_node1 = node1->next;
			if (node1->ntmp_addr)
			{
				printf("%p\n", node1->ntmp_addr);
				free(node1->ntmp_addr);
			}
			free(node1);
			node1 = n_node1;
		}
		(*collector)->ntmp_cltr = NULL;
	}
	else if (flag == ALL)
	{
		node = (*collector)->tmp_cltr;
		while (node)
		{
			n_node = node->next;
			if (node->tmp_addr)
			{
				printf("%p\n", node->tmp_addr);
				free(node->tmp_addr);
			}
			free(node);
			node = n_node;
		}
		node1 = (*collector)->ntmp_cltr;
		while (node1)
		{
			n_node1 = node1->next;
			if (node1->ntmp_addr)
			{
				printf("%p\n", node1->ntmp_addr);
				free(node1->ntmp_addr);
			}
			free(node1);
			node1 = n_node1;
		}
		free((*collector));
		(*collector) = NULL;
	}
}

void	*h_malloc(t_collector **collector, size_t s, void *p, t_flag flag)
{
	t_tmp 		*n_iter;
	t_ntmp 		*n_iter1;
	t_tmp 		*tmp_c;
	t_ntmp 		*ntmp_c;

	if (!(*collector))
	{
		(*collector) = malloc(sizeof(t_collector));
		(*collector)->tmp_cltr = NULL;
		(*collector)->ntmp_cltr = NULL;
	}
	if (flag == TMP)
	{
		tmp_c = malloc(sizeof(t_tmp));
		p = malloc(s);
		if (!tmp_c || !p || !(*collector))
		{
			write (2, "\033[0;32mMALLOC_FAILED\033[0;37m\n", 29);
			ft_collectorclear(collector, ALL);
			exit (1);
		}
		tmp_c->tmp_addr = p;
		tmp_c->next = NULL;
		if (!((*collector)->tmp_cltr))
		{
			((*collector)->tmp_cltr) = tmp_c;
			((*collector)->tmp_cltr)->next = NULL;
		}
		else
		{
			n_iter = (*collector)->tmp_cltr;
			while (n_iter->next)
				n_iter = n_iter->next;
			n_iter->next = tmp_c;
			tmp_c->next = NULL;
		}
	}
	else if (flag == NTMP)
	{
		ntmp_c = malloc(sizeof(t_ntmp));
		p = malloc(s);
		if (!ntmp_c || !p || !(*collector))
		{
			write (2, "\033[0;32mMALLOC_FAILED\033[0;37m\n", 29);
			ft_collectorclear(collector, ALL);
			exit (1);
		}
		ntmp_c->ntmp_addr = p;
		ntmp_c->next = NULL;
		if (!((*collector)->ntmp_cltr))
		{
			((*collector)->ntmp_cltr) = ntmp_c;
			((*collector)->ntmp_cltr)->next = NULL;
		}
		else
		{
			n_iter1 = (*collector)->ntmp_cltr;
			while (n_iter1->next)
				n_iter1 = n_iter1->next;
			n_iter1->next = ntmp_c;
			ntmp_c->next = NULL;
		}
	}
	return (p);
}
