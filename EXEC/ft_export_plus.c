/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_plus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 18:10:15 by msamhaou          #+#    #+#             */
/*   Updated: 2023/05/31 11:26:12 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_exp_var_exist(t_env *exp, char *str)
{
	char	*sub_origin;
	char	*sub_tocmp;
	int		trim_len;
	int		start_len;

	start_len = ft_strlen("declare -x ");
	sub_tocmp = ft_substr(str, 0, ft_trim_len(str, '='));
	while (exp)
	{
		trim_len = ft_trim_len(exp->str, '=');
		sub_origin = ft_substr(exp->str, start_len, \
			trim_len - ft_strlen("declare -x "));
		if (ft_strcmp(sub_origin, sub_tocmp) == 0)
			return (free(sub_tocmp), free(sub_origin), exp);
		free(sub_origin);
		exp = exp->next;
	}
	return (free(sub_tocmp), NULL);
}

void	ft_exp_add_back(t_env **env, char *str)
{
	char	*quoted;
	t_env	*exist;

	exist = ft_exp_var_exist(*env, str);
	if (exist)
	{
		quoted = ft_quote_it(str);
		free(str);
		ft_replace_exp_str(exist, quoted);
		free(quoted);
		return ;
	}
	quoted = ft_quote_it(str);
	env_add_back(env, new_env(quoted));
	free(quoted);
	ft_sort_env(*env);
}

t_env	*ft_set_export_lst(t_env *env_lst)
{
	t_env	*res;
	t_env	*toadd;
	char	*str;

	res = NULL;
	str = NULL;
	while (env_lst)
	{
		str = ft_quote_it(env_lst->str);
		toadd = new_env(str);
		free(str);
		env_add_back(&res, toadd);
		env_lst = env_lst->next;
	}
	ft_sort_env(res);
	return (res);
}
