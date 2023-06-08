/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_14.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:09:45 by idouni            #+#    #+#             */
/*   Updated: 2023/06/08 14:20:23 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	s_expa(t_struct *cable, char *s, char **str)
{
	if (searcher_for_spc(s))
		expand_evs(cable, s, str);
	else
		(*str) = ft_mstrjoin(cable, (*str), ft_getenv(cable, s), TMP);
}

void	s_expa2(t_struct *cable, char *s, char **str)
{
	if (ft_isdigit(s[0]))
		(*str) = ft_mstrjoin(cable, (*str), (s + 1), TMP);
	else if (s[0] == '?')
		expand_ev(cable, str, s);
	else if (searcher_for_spc(s))
		expand_evs(cable, s, str);
	else
		(*str) = ft_mstrjoin(cable, (*str), \
		ft_getenv(cable, s), TMP);
}

int 	spc_after_d(char *line)
{
	if (line[0] == '$' && (line[1] == '"' || line[1] == '\''))
		return (1);
	return (0);	
}

char	*s_expander(t_struct *cable, char *line)
{
	char	**s;
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	s = NULL;
	if (!line)
		return (NULL);
	if(!ft_strchr(line, '$') || spc_after_d(line))
	{
		str = ft_mstrdup(cable, line, TMP);
		free(line);
		return (str);
	}
	s = ft_msplit(cable, line, '$', TMP);
	if (!s[0])
		return ("$");
	if (line[0] == '$')
		s_expa(cable, s[i], &str);
	else
		str = ft_mstrjoin(cable, str, s[i], TMP);
	i++;
	while (s[i])
	{
		s_expa2(cable, s[i], &str);
		i++;
	}
	if (line[ft_strlen (line) - 1] == '$')
		str = ft_mstrjoin(cable, str, "$", TMP);
	free(line);
	return (str);
}

void	tmp_alloc(t_collector **collector, size_t s, void **p)
{
	t_tmp	*n_iter;
	t_tmp	*tmp_c;

	tmp_c = malloc(sizeof(t_tmp));
	(*p) = malloc(s);
	if (!tmp_c || !(*p) || !(*collector))
	{
		write (2, "\033[0;32mMALLOC_FAILED\033[0;37m\n", 29);
		ft_collectorclear(collector, ALL);
		exit (1);
	}
	tmp_c->tmp_addr = (*p);
	if (!((*collector)->tmp_cltr))
		((*collector)->tmp_cltr) = tmp_c;
	else
	{
		n_iter = (*collector)->tmp_cltr;
		while (n_iter->next)
			n_iter = n_iter->next;
		n_iter->next = tmp_c;
	}
	tmp_c->next = NULL;
}

void	ntmp_alloc(t_collector **collector, size_t s, void **p)
{
	t_ntmp	*n_iter1;
	t_ntmp	*ntmp_c;

	ntmp_c = malloc(sizeof(t_ntmp));
	(*p) = malloc(s);
	if (!ntmp_c || !(*p) || !(*collector))
	{
		write (2, "\033[0;32mMALLOC_FAILED\033[0;37m\n", 29);
		ft_collectorclear(collector, ALL);
		exit (1);
	}
	ntmp_c->ntmp_addr = (*p);
	if (!((*collector)->ntmp_cltr))
		((*collector)->ntmp_cltr) = ntmp_c;
	else
	{
		n_iter1 = (*collector)->ntmp_cltr;
		while (n_iter1->next)
			n_iter1 = n_iter1->next;
		n_iter1->next = ntmp_c;
	}
	ntmp_c->next = NULL;
}
