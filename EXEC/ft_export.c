/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 01:03:14 by msamhaou          #+#    #+#             */
/*   Updated: 2023/05/27 18:19:03 by msamhaou         ###   ########.fr       */
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

static void	ft_plus_eq_check(char	**str, t_env *env)
{
	t_env	*exist;
	char	*trimmed;

	exist = NULL;
	if (ft_strnstr(*str, "+=", ft_strlen(*str)))
	{
		*str = ft_trim_char(*str, '+');
		exist = ft_var_exist(env, *str);
		if (exist)
			*str = ft_strjoin(*str, ft_split(*str, '=')[1]);
	}
}

void	ft_put_err()
{
	ft_putendl_fd("minishell: not a valid identifier", 2);
}

char	**ft_export(t_init *init, char *str)
{
	char	**res;
	t_env	*head;
	t_env	*ev_var;

	head = init->envlst;
	if (ft_more_plus(str, '+'))
		return(ft_put_err(), init->myenv);
	ft_plus_eq_check(&str, init->envlst);
	ev_var = ft_var_exist(init->envlst, str);
	if (ev_var)
		ft_edit_env_str(ev_var, str);
	else
	{
		if (ft_strchr(str, '='))
			env_add_back(&init->envlst, new_env(str));
	}
	ft_exp_add_back(&init->exp_lst, str);
	init->envlst = head;
	res = ft_make_double_char(init->envlst);
	init->envlst = head;
	ft_free_stringp(init->myenv);
	return (res);
}
