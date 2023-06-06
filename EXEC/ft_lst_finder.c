/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_finder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 08:59:09 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/06 09:33:31 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envlst	*ft_var_env_exist(t_envlst *envlst, char *str)
{
	char	**var;
	char	**splstr;

	var = ft_soft_split(str, '=');
	while (envlst)
	{
		splstr = ft_soft_split(envlst->str, '=');
		if (!ft_strcmp(splstr[0], var[0]))
			return (ft_free_stringp(var), ft_free_stringp(splstr), envlst);
		envlst = envlst->next;
		ft_free_stringp(splstr);
	}
	ft_free_stringp(var);
	return (NULL);
}

t_exp	*ft_var_exp_exist(t_exp *exp, char *str)
{
	char	**var;
	char	**splstr;

	var = ft_soft_split(str, '=');
	while (exp)
	{
		splstr = ft_soft_split(exp->str, '=');
		if (!ft_strcmp(splstr[0], var[0]))
			return (ft_free_stringp(var), ft_free_stringp(splstr), exp);
		exp = exp->next;
		ft_free_stringp(splstr);
	}
	ft_free_stringp(var);
	return (NULL);
}
