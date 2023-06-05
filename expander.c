/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:20:04 by idouni            #+#    #+#             */
/*   Updated: 2023/06/05 21:43:14 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_c1(t_struct *cable, char *s, char **str, int *i)
{
	(*str) = ft_mstrdup(cable, s, TMP);
	(*i)++;
}

void	expand_ev(t_struct *cable, char **str, char *s)
{
	(*str) = ft_mstrjoin(cable, (*str), ft_mitoa(cable), TMP);
	(*str) = ft_mstrjoin(cable, (*str), s + 1, TMP);
}

void	expand_evs(t_struct *cable, char *s, char **str)
{
	int	l;

	l = searcher_for_spc(s);
	(*str) = ft_mstrjoin(cable, (*str), ft_getenv(cable, \
	ft_msubstr(cable, s, 0, l)), TMP);
	(*str) = ft_mstrjoin(cable, (*str), s + l, TMP);
}

void	expnd_2(t_struct *cable, t_lexer *node, char **str)
{
	int		i;
	char	**s;

	i = 0;
	s = ft_msplit(cable, node->cmd, '$', TMP);
	if (node->cmd[0] != '$')
		expand_c1(cable, s[i], str, &i);
	while (s[i])
	{
		if (ft_isdigit(s[i][0]))
			(*str) = ft_mstrjoin(cable, (*str), (s[i] + 1), TMP);
		else if (s[i][0] == '?')
			expand_ev(cable, str, s[i]);
		else if (searcher_for_spc(s[i]))
			expand_evs(cable, s[i], str);
		else
			(*str) = ft_mstrjoin(cable, (*str), \
			ft_getenv(cable, s[i]), TMP);
		i++;
	}
	if (node->cmd[ft_strlen (node->cmd) - 1] == '$')
		(*str) = ft_mstrjoin(cable, (*str), "$", TMP);
}

void	expander(t_struct *cable, t_lexer **head)
{
	t_lexer	*node;
	char	*str;
	int		exp;

	exp = 1;
	node = *head;
	while (node)
	{
		str = NULL;
		if (node->type == R_HD)
			exp = 0;
		else if ((node->type != ST_SQ) && (ft_strchr(node->cmd, '$')) && !exp)
			exp = 1;
		else if ((node->type != ST_SQ) && (ft_strchr(node->cmd, '$')) && exp)
		{
			expnd_v(cable, node, &str);
			node->cmd = ft_mstrdup(cable, str, TMP);	
		}
		node = node->next;
	}
}

char	*s_expander(t_struct *cable, char *line)
{
	char **s;
	int i = 0;
	char *str;

	str = NULL;
	s = NULL;
	if (!line || !ft_strchr(line, '$'))
		return(line);

	s = ft_msplit(cable, line, '$', TMP);
	if (!s[0])
		return ("$");
	if (line[0] == '$')
	{
		if (searcher_for_spc(s[i]))
			expand_evs(cable, s[i], &str);
		else
			str = ft_mstrjoin(cable, str, ft_getenv(cable, s[i]), TMP);
	}
	else
		str = ft_mstrjoin(cable, str, s[i], TMP);
	i++;
	while(s[i])
	{
		if (ft_isdigit(s[i][0]))
			str = ft_mstrjoin(cable, str, (s[i] + 1), TMP);
		else if (s[i][0] == '?')
			expand_ev(cable, &str, s[i]);
		else if (searcher_for_spc(s[i]))
			expand_evs(cable, s[i], &str);
		else
			str = ft_mstrjoin(cable, str, \
			ft_getenv(cable, s[i]), TMP);
		i++;
	}
	if (line[ft_strlen (line) - 1] == '$')
		str = ft_mstrjoin(cable, str, "$", TMP);
	return (str);
}

