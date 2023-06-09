/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_16.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:09:45 by idouni            #+#    #+#             */
/*   Updated: 2023/06/19 18:01:54 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pcheck_head(t_lexer **h_lexer)
{
	t_lexer	*node;

	node = *h_lexer;
	while (node)
	{
		if (node->type == WH_SP)
			node = node->next;
		else if (node->type != PIP)
			break ;
		else if (node->type == PIP)
			return (syntx_err(), 1);
	}
	return (0);
}

int	pcheck_bdy(t_lexer **h_lexer)
{
	t_lexer	*node;
	t_lexer	*tmp;

	tmp = NULL;
	node = *h_lexer;
	while (node)
	{
		if ((node->type == PIP) && (node->next))
		{
			tmp = node->next;
			while (tmp)
			{
				if (tmp->type == SCMD || tmp->type == ST_SQ \
				|| tmp->type == ST_DQ)
					return (0);
				else if (tmp->type == PIP)
					return (syntx_err(), 1);
				tmp = tmp->next;
			}
		}
		node = node->next;
	}
	return (0);
}

int	pcheck_tail(t_lexer **h_lexer)
{
	t_lexer	*node;
	t_lexer	*tmp;

	tmp = NULL;
	node = *h_lexer;
	while (node)
	{
		if (node->type == PIP)
			tmp = node;
		else if (node->type == SCMD || node->type == ST_SQ \
		|| node->type == ST_DQ)
			tmp = node;
		node = node->next;
	}
	if (tmp && tmp->type == PIP)
		return (syntx_err(), 1);
	return (0);
}

int	basic_syntax_check2(t_lexer **h_lexer)
{
	t_lexer	*node;

	node = *h_lexer;
	while (node)
	{
		if (node->type == SCMD && check_for_udf(node->cmd))
			return (syntx_err(), 1);
		node = node->next;
	}
	return (0);
}
