/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:42:06 by idouni            #+#    #+#             */
/*   Updated: 2023/05/23 16:19:34 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dq_lex(t_collector **collector, t_lexer **l_node, char *s, int *i)
{
	int		start;
	int		l;

	l = 0;
	(*i)++;
	start = *i;
	while (s[(*i)] != '"' && s[(*i)])
	{
		(*i)++;
		l++;
	}
	add_lexer(collector, l_node, ft_msubstr(collector, s, start, l), ST_DQ);
	(*i)++;
}

void	sq_lex(t_collector **collector, t_lexer **l_node, char *s, int *i)
{
	int		start;
	int		l;

	l = 0;
	(*i)++;
	start = *i;
	while (s[(*i)] != '\'' && s[(*i)])
	{
		(*i)++;
		l++;
	}
	add_lexer(collector, l_node, ft_msubstr(collector, s, start, l), ST_SQ);
	(*i)++;
}

void	scmd_lex(t_collector **collector, t_lexer **l_node, char *s, int *i)
{
	int		start;
	int		l;

	l = 0;
	start = (*i);
	while (ft_isascii(s[(*i)]) && s[(*i)] && s[(*i)] != '>' && s[(*i)] != '<' \
	&& s[(*i)] != '|' && s[(*i)] != '\'' && s[(*i)] != '"' && s[(*i)] != ' ')
	{
		(*i)++;
		l++;
	}
	add_lexer(collector, l_node, ft_msubstr(collector, s, start, l), SCMD);
}

void	lexer_p2(t_collector **collector, t_lexer **l_node, char *s, int sz)
{
	int	i;

	i = 0;
	while (i < sz && s[i])
	{
		if (s[i] == '"')
			dq_lex(collector, l_node, s, &i);
		else if (s[i] == '\'')
			sq_lex(collector, l_node, s, &i);
		else if (ft_isascii(s[i]) && s[i] && s[i] != '>' && s[i] != '<' \
		&& s[i] != '|' && s[i] != '\'' && s[i] != '"' && s[i] != ' ')
			scmd_lex(collector, l_node, s, &i);
		else if (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
			whsp_lex(collector, l_node, s, &i);
		else if (s[i] == '|')
			pip_lex(collector, l_node, s, &i);
		else if (s[i] == '>' && s[i + 1] != '>')
			rot_lex(collector, l_node, s, &i);
		else if (s[i] == '<' && s[i + 1] != '<')
			rin_lex(collector, l_node, s, &i);
		else if (s[i] == '>' && s[i + 1] == '>')
			roa_lex(collector, l_node, s, &i);
		else if (s[i] == '<' && s[i + 1] == '<')
			rhd_lex(collector, l_node, s, &i);
	}
}

t_lexer	*lexer(t_collector **collector, char *s)
{
	int		sz;
	t_lexer	*l_node;

	sz = ft_strlen(s);
	l_node = NULL;
	lexer_p2(collector, &l_node, s, sz);
	free(s);
	return (l_node);
}
