/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:03:36 by msamhaou          #+#    #+#             */
/*   Updated: 2023/05/26 12:05:45 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 || *s2)
	{
		if ((*s1 > *s2) || (*s1 < *s2))
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (0);
}

void	ft_printlst(t_env *lst)
{
	while (lst)
	{
		ft_putendl_fd(lst->str, STDOUT_FILENO);
		lst = lst->next;
	}
}

static void	ft_swap_str(t_env *a, t_env *b)
{
	char	*tmp;

	tmp = a->str;
	a->str = b->str;
	b->str = tmp;
}

void	ft_sort_env(t_env *envlst)
{
	t_env *head;
	int	swapped;

	head = envlst;
	swapped = 1;
	while (swapped)
	{
		envlst = head;
		swapped = 0;
		while (envlst->next)
		{
			if (ft_strcmp(envlst->str, envlst->next->str) > 0)
			{
				ft_swap_str(envlst, envlst->next);
				swapped = 1;
			}
			envlst = envlst->next;
		}
	}
}
