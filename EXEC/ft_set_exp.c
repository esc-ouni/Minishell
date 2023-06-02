/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_exp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 11:46:21 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/02 14:01:36 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_swap_str(t_env *a, t_env *b)
{
	char	*tmp;

	tmp = a->str;
	a->str = b->str;
	b->str = tmp;
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
	t_env	*env;
	t_exp	*exp;

	cable->exp = NULL;
	env = cable->envlst;
	while (env)
	{
		ft_exp_add_back(cable->exp, ft_exp_new_node(env->str));
		env = env->next;
	}
}

void	ft_alpha_order(t_struct *cable)
{
	t_exp	*exp;

	exp = cable->exp;
	while (exp->next)
	{
		if (strcmp(exp->str, exp->next->str) > 0)
			ft_swap_str(exp->str, exp->next->str);
		exp = exp->next;
	}
}

void	ft_exp_set(t_struct *cable, char **ev)
{
	ft_cpy_env_to_exp(cable);
	ft_alpha_order(cable);
}
