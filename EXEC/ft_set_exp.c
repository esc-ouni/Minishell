/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_exp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 11:46:21 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/05 15:46:39 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_swap_str(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

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

void	ft_cpy_env_to_exp(t_struct *cable)
{
	t_envlst	*env;
	char		*newstr;
	t_exp	*exp;

	cable->exp = NULL;
	env = cable->envlst;
	while (env)
	{
		newstr = ft_exported_str(env->str, cable);
		ft_exp_add_back(&cable->exp, ft_exp_new_node(newstr, cable));
		env = env->next;
	}
}

void	ft_alpha_order(t_struct *cable)
{
	t_exp	*exp;
	t_exp	*head;
	int	swapped;

	exp = cable->exp;
	head = exp;
	swapped = 1;
	while(swapped)
	{
		exp = head;
		swapped = 0;
		while (exp->next)
		{
			if (ft_strcmp(exp->str, exp->next->str) > 0)
			{
				ft_swap_str(&exp->str, &exp->next->str);
				swapped = 1;
				break ;
			}
			exp = exp->next;
		}
	}
}

void	ft_exp_set(t_struct *cable)
{
	ft_cpy_env_to_exp(cable);
	ft_alpha_order(cable);
}
