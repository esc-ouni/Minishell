#include "minishell.h"

t_lexer *lexer(t_collector **collector, char *s)
{
    int     i;
    int     l2;
    int     start;
    int     sz;
    t_lexer *l_node;

    i = 0;
    start = 0;
    l2 = 0;
    sz = ft_strlen(s);
    l_node = NULL;
    while (i < sz && s[i])
    {
        if (s[i] == '"')
        {
            if (!start)
                start = i + 1;
            i++;
            while (s[i] != '"' && s[i])
            {
                i++;
                l2++;
            }
            add_lexer(collector, &l_node, ft_msubstr(collector, s, start, l2), ST_DQ);
            start = 0;
            l2 = 0;
            i++;
        }
        else if (s[i] == '\'')
        {
            if (!start)
                start = i + 1;
            i++;
            while (s[i] != '\'' && s[i])
            {
                i++;
                l2++;
            }
            add_lexer(collector, &l_node, ft_msubstr(collector, s, start, l2), ST_SQ);
            start = 0;
            l2 = 0;
            i++;
        }
        else if (ft_isascii(s[i]) && s[i] && s[i] != '>' && s[i] != '<' && s[i] != '|' && s[i] != '\'' && s[i] != '"' && s[i] != ' ')
        {
            if (!start)
                start = i;
            while (ft_isascii(s[i]) && s[i] && s[i] != '>' && s[i] != '<' && s[i] != '|' && s[i] != '\'' && s[i] != '"' && s[i] != ' ')
            {
                i++;
                l2++;
            }
            add_lexer(collector, &l_node, ft_msubstr(collector, s, start, l2), SCMD);
            start = 0;
            l2 = 0;
        }
        else if (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		{
			add_lexer(collector, &l_node, ft_msubstr(collector, s, i, 1), WH_SP);
            i += 1;
            start = 0;
            l2 = 0;
		}
        else if (s[i] == '|')
        {
            add_lexer(collector, &l_node, ft_msubstr(collector, s, i, 1), PIP);
            i += 1;
            start = 0;
            l2 = 0;
        }
        else if (s[i] == '>' && s[i + 1] != '>')
        {
            add_lexer(collector, &l_node, ft_msubstr(collector, s, i, 1), R_OT);
            i += 1;
            start = 0;
            l2 = 0;
        }
        else if (s[i] == '<' && s[i + 1] != '<')
        {
            add_lexer(collector, &l_node, ft_msubstr(collector, s, i, 1), R_IN);
            i += 1;
            start = 0;
            l2 = 0;
        }
        else if (s[i] == '>' && s[i + 1] == '>')
        {
            add_lexer(collector, &l_node, ft_msubstr(collector, s, i, 2), R_OA);
            i += 2;
            start = 0;
            l2 = 0;
        }
        else if (s[i] == '<' && s[i + 1] == '<')
        {
            add_lexer(collector, &l_node, ft_msubstr(collector, s, i, 2), R_HD);
            i += 2;
            start = 0;
            l2 = 0;
        }
    }
	free(s);
    return (l_node);
}
