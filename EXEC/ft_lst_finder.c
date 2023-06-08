/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_finder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 08:59:09 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/08 16:16:40 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envlst	*ft_var_env_exist(t_envlst *envlst, char *str, t_struct *cable)
{
	char	**var;
	char	**splstr;

	var = ft_soft_split(str, '=', cable);
	while (envlst)
	{
		splstr = ft_soft_split(envlst->str, '=', cable);
		if (!ft_strcmp(splstr[0], var[0]))
			return (envlst);
		envlst = envlst->next;
	}
	return (NULL);
}

t_exp	*ft_var_exp_exist(t_exp *exp, char *str, t_struct *cable)
{
	char	**var;
	char	**splstr;

	var = ft_soft_split(str, '=', cable);
	while (exp)
	{
		splstr = ft_soft_split(exp->str, '=', cable);
		if (!ft_strcmp(splstr[0], var[0]))
			return (exp);
		exp = exp->next;
	}
	return (NULL);
}
