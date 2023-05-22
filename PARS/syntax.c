/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:20:37 by idouni            #+#    #+#             */
/*   Updated: 2023/05/22 17:45:16 by idouni           ###   ########.fr       */
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

int	check_pipes(char *s)
{
	int	i;

	i = 0;
	if ((s[i] == '|') || s[ft_strlen(s)-1] == '|')
		return (syntx_err(), 1);
	while (s[i])
	{
		if (s[i + 1] && s[i] == '|' && s[i + 1] == '|')
			return (syntx_err(), 1);
		i++;
	}
	return (0);
}

void	syntx_err(void)
{
	write(2, "syntax error ...\n", 18);
}
