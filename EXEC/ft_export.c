/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 01:03:14 by msamhaou          #+#    #+#             */
/*   Updated: 2023/05/22 02:46:34 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_edit_env_str(t_env *to_edit, char *str)
{
	free(to_edit->str);
	to_edit->str = ft_strdup(str);
	return (0);
}

static t_env	*ft_var_exist(t_env *env_lst, char *str)
{
	char	**var;

	var = ft_split(str, '=');
	while (env_lst)
	{
		if (!ft_strncmp(env_lst->str, var[0], ft_strlen(var[0])))
			return (env_lst);
		env_lst = env_lst->next;
	}
	ft_free_stringp(var);
	return (NULL);
}

static int	ft_is_exported(char *str)
{
	if (str && ft_isalpha(str[0]) && ft_strchr(str, '='))
		return (1);
	return (0);
}

char	**ft_export(t_env **env_lst, char *str, char **myenv)
{
	char	**res;
	t_env	*head;
	t_env	*ev_var;

	if (!ft_is_exported(str))
		return (myenv);
	head = *env_lst;
	ev_var = ft_var_exist(*env_lst, str);
	if (ev_var)
		ft_edit_env_str(ev_var, str);
	else
		env_add_back(env_lst, new_env(str));
	*env_lst = head;
	res = ft_make_double_char(*env_lst);
	*env_lst = head;
	ft_free_stringp(myenv);
	return (res);
}
