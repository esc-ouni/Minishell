#include "Minishell.h"

void	dq_lex(t_collector **collector, t_lexer **l_node, char *s, int *i)
{
    int     start;
    int     l;

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
    int     start;
    int     l;

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
    int     start;
    int     l;

	l = 0;
	start = (*i);
	while (ft_isascii(s[(*i)]) && s[(*i)] && s[(*i)] != '>' && s[(*i)] != '<' && s[(*i)] != '|' && s[(*i)] != '\'' && s[(*i)] != '"' && s[(*i)] != ' ')
	{
		(*i)++;
		l++;
	}
	add_lexer(collector, l_node, ft_msubstr(collector, s, start, l), SCMD);
}

void	whsp_lex(t_collector **collector, t_lexer **l_node, char *s, int *i)
{
	add_lexer(collector, l_node, ft_msubstr(collector, s, (*i), 1), WH_SP);
	(*i) += 1;
}

void	pip_lex(t_collector **collector, t_lexer **l_node, char *s, int *i)
{
	add_lexer(collector, l_node, ft_msubstr(collector, s, *i, 1), PIP);
	(*i) += 1;
}

void	rot_lex(t_collector **collector, t_lexer **l_node, char *s, int *i)
{
	add_lexer(collector, l_node, ft_msubstr(collector, s, (*i), 1), R_OT);
	(*i) += 1;
}

void	rin_lex(t_collector **collector, t_lexer **l_node, char *s, int *i)
{
	add_lexer(collector, l_node, ft_msubstr(collector, s, (*i), 1), R_IN);
	(*i) += 1;
}

void	roa_lex(t_collector **collector, t_lexer **l_node, char *s, int *i)
{
	add_lexer(collector, l_node, ft_msubstr(collector, s, (*i), 2), R_OA);
	(*i) += 2;
}

void	rhd_lex(t_collector **collector, t_lexer **l_node, char *s, int *i)
{
	add_lexer(collector, l_node, ft_msubstr(collector, s, (*i), 2), R_HD);
	(*i) += 2;
}

t_lexer *lexer(t_collector **collector, char *s)
{
    int     i;
    int     sz;
    t_lexer *l_node;

    i = 0;
    sz = ft_strlen(s);
    l_node = NULL;
    while (i < sz && s[i])
    {
		if (s[i] == '"')
			dq_lex(collector, &l_node, s, &i);
        else if (s[i] == '\'')
			sq_lex(collector, &l_node, s, &i);
        else if (ft_isascii(s[i]) && s[i] && s[i] != '>' && s[i] != '<' && s[i] != '|' && s[i] != '\'' && s[i] != '"' && s[i] != ' ')
			scmd_lex(collector, &l_node, s, &i);
        else if (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
			whsp_lex(collector, &l_node, s, &i);
        else if (s[i] == '|')
			pip_lex(collector, &l_node, s, &i);
        else if (s[i] == '>' && s[i + 1] != '>')
			rot_lex(collector, &l_node, s, &i);
        else if (s[i] == '<' && s[i + 1] != '<')
			rin_lex(collector, &l_node, s, &i);
        else if (s[i] == '>' && s[i + 1] == '>')
			roa_lex(collector, &l_node, s, &i);
        else if (s[i] == '<' && s[i + 1] == '<')
			rhd_lex(collector, &l_node, s, &i);
    }
	free(s);
    return (l_node);
}
