#include "minishell.h"

int	check_oerr(char *s)
{
	int i = 0;
	int sq = 0;
	int dq = 0;

	while (s[i])
	{
		if (s[i] == '\'')
		{
			sq++;
			i++;
			while (s[i] != '\'' && s[i])
				i++;
			if (s[i] == '\'')
			{
				sq++;
				i++;
			}
		}
		else if (s[i] == '"')
		{
			dq++;
			i++;
			while (s[i] != '"' && s[i])
				i++;
			if (s[i] == '"')
			{
				dq++;
				i++;
			}
		}
		else
			i++;
	}
	if ((sq % 2) || (dq % 2))
	{
		write(2, "syntax error near unexpected token\n", 35);
		return (1);
	}
	return (0);
}

int	check_pipes(char *s)
{
	int i = 0;

	if ((s[i] == '|') || s[ft_strlen(s)-1] == '|')
	{
		write(2, "syntax error near unexpected token\n", 35);
		return (1);
	}
	while (s[i])
	{
		if (s[i+1] && s[i] == '|' && s[i+1] == '|')
		{
			write(2, "syntax error near unexpected token\n", 35);
			return (1);
		}
		i++;
	}
	return (0);
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

int	check_syntax2(t_lexer	**h_lexer)
{
	t_lexer *node;

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
			{
				printf("syntax error near unexpected token\n");
				return (1);
			}
			else if (!node)
			{
				printf("syntax error near unexpected token\n");
				return (1);
			}
			node = node->next;
		}
		else
			node = node->next;
	}
	return (0);
}
