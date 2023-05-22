/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:20:04 by idouni            #+#    #+#             */
/*   Updated: 2023/05/22 17:14:36 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	searcher_for_spc(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '$' && s[i] != '*' && s[i] != '+' && s[i] != '-' && \
	s[i] != '>' && s[i] != '<' && s[i] != '\\' && s[i] != '|' && s[i] != '!' \
	&& s[i] != '#' && s[i] != ' ' && s[i] != '\t' && s[i] != '\'')
		i++;
	return (i);
}

void	expand_c1(t_collector **collector, char *s ,char **str, int *i)
{
	(*str) = ft_mstrdup(collector, s);
	(*i)++;
}

void	expand_ev(t_collector **collector, char **str, char *s)
{
	(*str) = ft_mstrjoin(collector, (*str), ft_itoa(g_exit_val));
	(*str) = ft_mstrjoin(collector, (*str), s + 1);
}

void	expand_evs(t_collector **collector, char *s ,char **str, t_env **env)
{
	int	l;

	l = searcher_for_spc(s);
	(*str) = ft_mstrjoin(collector, (*str), ft_getenv(collector, \
	ft_msubstr(collector, s, 0, l), env));
	(*str) = ft_mstrjoin(collector, (*str), s + l);
}

void	expnd_2(t_collector **collector, t_env **env, t_lexer *node, char **str)
{
	int		i;
	char	**s;

	i = 0;
	s = ft_msplit(collector, node->cmd, '$');
	if (node->cmd[0] != '$')
		expand_c1(collector, s[i], str, &i);
	while (s[i])
	{
		if (ft_isdigit(s[i][0]))
			(*str) = ft_mstrjoin(collector, (*str), s[i]+1);
		else if (s[i][0] == '?')
			expand_ev(collector, str, s[i]);
		else if (searcher_for_spc(s[i]))
			expand_evs(collector, s[i], str, env);
		else
			(*str) = ft_mstrjoin(collector, (*str), ft_getenv(collector, s[i], env));
		i++;
	}
}

void	expander(t_collector **collector, t_env **env, t_lexer **head)
{
	t_lexer	*node;
	char	**s;
	char	*str;

	s = NULL;
	str = NULL;
	node = *head;
	while (node)
	{
		if ((node->type != ST_SQ) && (ft_strchr(node->cmd, '$')))
		{
			if (ft_strlen(node->cmd) == 1 && node->cmd[0] == '$')
				break ;
			else
			{
				expnd_2(collector, env, node, &str);
				if (node->cmd[ft_strlen (node->cmd) - 1] == '$')
					str = ft_mstrjoin(collector, str, "$");
			}
			node->cmd = ft_mstrdup(collector, str);
		}
		str = NULL;
		s = NULL;
		node = node->next;
	}
}
