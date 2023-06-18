/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:42:06 by idouni            #+#    #+#             */
/*   Updated: 2023/06/18 13:46:22 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dq_lex(t_struct *cable, t_lexer **l_node, char *s, int *i)
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
	add_lexer(cable, l_node, ft_msubstr(cable, s, start, l), ST_DQ);
	(*i)++;
}

void	sq_lex(t_struct *cable, t_lexer **l_node, char *s, int *i)
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
	add_lexer(cable, l_node, ft_msubstr(cable, s, start, l), ST_SQ);
	(*i)++;
}

void	scmd_lex(t_struct *cable, t_lexer **l_node, char *s, int *i)
{
	int		start;
	int		l;

	l = 0;
	start = (*i);
	while (ft_isprint(s[(*i)]) && s[(*i)] && s[(*i)] != '>' && s[(*i)] != '<' \
	&& s[(*i)] != '|' && s[(*i)] != '\'' && s[(*i)] != '"' && s[(*i)] != ' ')
	{
		(*i)++;
		l++;
	}
	add_lexer(cable, l_node, ft_msubstr(cable, s, start, l), SCMD);
}

void	lexer_p2(t_struct *cable, t_lexer **l_node, char *s, int sz)
{
	int	i;

	i = 0;
	while (i < sz && s[i])
	{
		if (s[i] == '"')
			dq_lex(cable, l_node, s, &i);
		else if (s[i] == '\'')
			sq_lex(cable, l_node, s, &i);
		else if (ft_isprint(s[i]) && s[i] && s[i] != '>' && s[i] != '<' \
		&& s[i] != '|' && s[i] != '\'' && s[i] != '"' && s[i] != ' ')
			scmd_lex(cable, l_node, s, &i);
		else if (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
			whsp_lex(cable, l_node, s, &i);
		else if (s[i] == '|')
			pip_lex(cable, l_node, s, &i);
		else if (s[i] == '>' && s[i + 1] != '>')
			rot_lex(cable, l_node, s, &i);
		else if (s[i] == '<' && s[i + 1] != '<')
			rin_lex(cable, l_node, s, &i);
		else if (s[i] == '>' && s[i + 1] == '>')
			roa_lex(cable, l_node, s, &i);
		else if (s[i] == '<' && s[i + 1] == '<')
			rhd_lex(cable, l_node, s, &i);
	}
}

t_lexer	*lexer(t_struct *cable, char *s)
{
	int		sz;
	t_lexer	*l_node;

	sz = ft_strlen(s);
	l_node = NULL;
	lexer_p2(cable, &l_node, s, sz);
	add_history(s);
	free(s);
	return (l_node);
}
