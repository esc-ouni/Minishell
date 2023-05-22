/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:20:37 by idouni            #+#    #+#             */
/*   Updated: 2023/05/22 16:22:06 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

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

int	check_pipes(char *s)
{
	int i = 0;

	if ((s[i] == '|') || s[ft_strlen(s)-1] == '|')
		return (syntx_err(), 1);
	while (s[i])
	{
		if (s[i+1] && s[i] == '|' && s[i+1] == '|')
			return (syntx_err(), 1);
		i++;
	}
	return (0);
}

void	syntx_err(void)
{
	write(2, "syntax error ...\n", 18);
}

int	check_syntax(char *s)
{
	if (!s)
		write(1, "exit\n", 5), exit(0);
	if (!ft_strlen(s))
		return (1);
	add_history(s);
	if (check_oerr(s))
		return (1);
	if (check_pipes(s))
		return (1);
	return (0);
}

int	check_syntax2(t_lexer **h_lexer)
{
	t_lexer	*node;

	node = *h_lexer;
	while (node)
	{
		if (node->type == WH_SP)
			node = node->next;
		else if ((node->type == R_OA) || (node->type == R_OT) || (node->type == R_IN) || (node->type == R_HD))
		{
			node = node->next;
			while (node && node->type == WH_SP)
				node = node->next;
			if ((node) && ((node->type == R_OA) || (node->type == R_OT) || (node->type == R_IN) || (node->type == R_HD || node->type == PIP)))
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
