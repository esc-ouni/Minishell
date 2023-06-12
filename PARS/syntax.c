/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:20:37 by idouni            #+#    #+#             */
/*   Updated: 2023/06/12 14:21:00 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	count_sq(char *s, int *i, int *sq)
{
	(*sq)++;
	(*i)++;
	while (s[(*i)] != '\'' && s[(*i)])
		(*i)++;
	if (s[(*i)] == '\'')
	{
		(*sq)++;
		(*i)++;
	}
}

void	count_dq(char *s, int *i, int *dq)
{
	(*dq)++;
	(*i)++;
	while (s[(*i)] != '"' && s[(*i)])
		(*i)++;
	if (s[(*i)] == '"')
	{
		(*dq)++;
		(*i)++;
	}
}

int	check_oerr(char *s)
{
	int	i;
	int	sq;
	int	dq;

	i = 0;
	sq = 0;
	dq = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			count_sq(s, &i, &sq);
		else if (s[i] == '"')
			count_dq(s, &i, &dq);
		else
			i++;
	}
	if ((sq % 2) || (dq % 2))
		return (syntx_err(), 1);
	return (0);
}

int	check_pipes(t_lexer **h_lexer)
{
	t_lexer	*node;
	t_lexer	*tmp;

	tmp = NULL;
	node = *h_lexer;
	while (node)
	{
		if (node->type != PIP)
		{
			tmp = NULL;
			break ;
		}
		if (node->type == PIP)
			return (syntx_err(), 1);
		if (node->type == WH_SP)
			node = node->next;
	}
	node = *h_lexer;
	while (node)
	{
		if (node->type == PIP && node->next)
		{
			tmp = node->next;
			while (tmp)
			{
				if (tmp->type == SCMD || node->type == ST_SQ || node->type == ST_DQ)
				{
					tmp = NULL;
					break ;
				}
				if(tmp->type == PIP)
					return (syntx_err(), 1);
				if (tmp->type == WH_SP || tmp->type != SCMD)
					tmp = tmp->next;
			}
		}
		node = node->next;
	}
	node = *h_lexer;
	tmp = NULL;
	while (node)
	{
		if (node->type == PIP)
			tmp = node;
		else if (node->type == SCMD || node->type == ST_SQ || node->type == ST_DQ)
			tmp = node;
		node = node->next;
	}
	if (tmp && tmp->type == PIP)
		return (syntx_err(), 1);
	return (0);
}

void	syntx_err(void)
{
	write(2, "syntax error ...\n", 18);
}
