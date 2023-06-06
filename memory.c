/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:20:18 by idouni            #+#    #+#             */
/*   Updated: 2023/06/06 15:12:43 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_tmp(t_collector **collector)
{
	t_tmp	*node;
	t_tmp	*n_node;

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

void	free_ntmp(t_collector **collector)
{
	t_ntmp	*node1;
	t_ntmp	*n_node1;

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

void	ft_collectorclear(t_collector **collector, t_flag flag)
{
	if (!(*collector) || !collector)
		return ;
	if (flag == TMP)
		free_tmp(collector);
	else if (flag == NTMP)
		free_ntmp(collector);
	else if (flag == ALL)
	{
		free_tmp(collector);
		free_ntmp(collector);
		free((*collector));
		(*collector) = NULL;
		rl_clear_history();
		exit(0);
	}
}

void head_alloc(t_collector **collector)
{
	(*collector) = malloc(sizeof(t_collector));
	if (*collector)
	{
		(*collector)->tmp_cltr = NULL;
		(*collector)->ntmp_cltr = NULL;
	}
}

void	tmp_alloc(t_collector **collector, size_t s, void **p)
{
	t_tmp 		*n_iter;
	t_tmp 		*tmp_c;

	tmp_c = malloc(sizeof(t_tmp));
	(*p) = malloc(s);
	if (!tmp_c || !(*p) || !(*collector))
	{
		write (2, "\033[0;32mMALLOC_FAILED\033[0;37m\n", 29);
		ft_collectorclear(collector, ALL);
		exit (1);
	}
	tmp_c->tmp_addr = (*p);
	if (!((*collector)->tmp_cltr))
		((*collector)->tmp_cltr) = tmp_c;
	else
	{
		n_iter = (*collector)->tmp_cltr;
		while (n_iter->next)
			n_iter = n_iter->next;
		n_iter->next = tmp_c;
	}
	tmp_c->next = NULL;
}

void	ntmp_alloc(t_collector **collector, size_t s, void **p)
{
	t_ntmp 		*n_iter1;
	t_ntmp 		*ntmp_c;

	ntmp_c = malloc(sizeof(t_ntmp));
	(*p) = malloc(s);
	if (!ntmp_c || !(*p) || !(*collector))
	{
		write (2, "\033[0;32mMALLOC_FAILED\033[0;37m\n", 29);
		ft_collectorclear(collector, ALL);
		exit (1);
	}
	ntmp_c->ntmp_addr = (*p);
	if (!((*collector)->ntmp_cltr))
		((*collector)->ntmp_cltr) = ntmp_c;
	else
	{
		n_iter1 = (*collector)->ntmp_cltr;
		while (n_iter1->next)
			n_iter1 = n_iter1->next;
		n_iter1->next = ntmp_c;
	}
	ntmp_c->next = NULL;
}

void	*h_malloc(t_collector **collector, size_t s, void *p, t_flag flag)
{
	if (!(*collector))
		head_alloc(collector);
	if (flag == TMP)
		tmp_alloc(collector, s, &p);
	else if (flag == NTMP)
		ntmp_alloc(collector, s, &p);
	return (p);
}
