/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:32:34 by idouni            #+#    #+#             */
/*   Updated: 2023/04/04 14:32:56 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// # include "minishell_pars.h"
#include "Minishell.h"

void	free_collect(t_collector **collect_head)
{
	t_collector *tmp;
	t_collector *tmp2;
	tmp = *collect_head;

	while (tmp)
	{
		tmp2 = tmp->next;
		free(tmp);
		tmp = NULL;
		tmp = tmp2;
	}
}

void	*h_malloc(t_collector **collector_head, size_t s, void *p)
{
	t_collector *tmp;
    t_collector *new_node;
	new_node = malloc(sizeof(t_collector));
	p = malloc(s);
	if (!new_node || !p)
	{
		printf("MALLOC\n");
		ft_collectorclear(collector_head);
		exit (1);
	}
	new_node->addr = p;
    if (!(*collector_head))
    {
        *collector_head = new_node;
        new_node->next = NULL;
    }
    else
    {
        tmp = *collector_head;
        while (tmp->next)
        {
            tmp = tmp->next;
        }
        tmp->next = new_node;
        new_node->next = NULL;
    }
	return (p);
}

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
