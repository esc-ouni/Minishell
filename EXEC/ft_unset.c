/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 01:10:12 by msamhaou          #+#    #+#             */
/*   Updated: 2023/05/21 01:14:09 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_isunset(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static t_env	*ft_is_unset_exist(t_env *env_lst, char *str)
{
	char	**every_str;

	while (env_lst)
	{
		every_str = ft_split(env_lst->str, '=');
		if (!ft_strncmp(every_str[0], str, ft_strlen(str)))
		{
			ft_free_stringp(every_str);
			return (env_lst);
		}
		ft_free_stringp(every_str);
		env_lst = env_lst->next;
	}
	return (NULL);
}

static t_env	*ft_find_prev(t_env *env_lst, t_env *env_node)
{
	while (env_lst)
	{
		if (env_lst->next == env_node)
			return (env_lst);
		env_lst = env_lst->next;
	}
	return (NULL);
}

static void	ft_remove_node(t_env **env_lst, t_env *to_remove)
{
	t_env	*previous_node;

	if (*env_lst == to_remove)
	{
		*env_lst = to_remove->next;
		free(to_remove);
	}
	previous_node = ft_find_prev(*env_lst, to_remove);
	if (previous_node)
	{
		if (!to_remove->next)
			previous_node->next = NULL;
		else
			previous_node->next = to_remove->next;
		free(to_remove);
	}
}

char	**ft_unset(t_env **env_lst, char *str, char **myenv)
{
	t_env	*to_unset;
	char	**res;

	if (!ft_isunset(str))
		return (myenv);
	to_unset = ft_is_unset_exist(*env_lst, str);
	if (!to_unset)
		return (myenv);
	else
		ft_remove_node(env_lst, to_unset);
	res = ft_make_double_char(*env_lst);
	ft_free_stringp(myenv);
	return (res);
}
