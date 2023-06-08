/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:11:12 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/08 11:49:37 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_exported_str(char *str, t_struct *cable)
{
	char	**eq;
	char	*left;
	char	*right;

	eq = ft_msoft_split_include(str, '=', cable);
	left = ft_mstrjoin(cable, "declare -x ", eq[0], NTMP);
	if (!eq[1][0] && !ft_strchr(eq[0], '='))
		return (left);
	right = ft_mstrjoin(cable, "\"", eq[1], TMP);
	right = ft_mstrjoin(cable, right, "\"", TMP);
	left = ft_mstrjoin(cable, left, right, NTMP);
	return (left);
}

char	**ft_make_double_char(t_envlst *envlst)
{
	int		i;
	char	**res;

	i = ft_envlst_size(envlst);
	res = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (envlst)
	{
		res[i] = ft_strdup(envlst->str);
		i++;
		envlst = envlst->next;
	}
	res[i] = NULL;
	return (res);
}

void	ft_env_update(t_struct *cable)
{
	cable->env = ft_make_double_char(cable->envlst);
}

void	ft_export(t_struct *cable, char	*str)
{
	if (!str)
		ft_print_exp(cable->exp);
	if (!ft_valid_var(str))
		return (ft_print_var_err(str, 0));
	if (ft_isplus(str))
		ft_joint_to_export(cable, &str);
	if (ft_strchr(str, '='))
	{
		if (ft_export_env(cable, str))
			ft_env_update(cable);
	}
	ft_export_exp(cable, str);
}
