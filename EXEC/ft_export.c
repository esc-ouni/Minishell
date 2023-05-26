/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 01:03:14 by msamhaou          #+#    #+#             */
/*   Updated: 2023/05/26 13:01:16 by msamhaou         ###   ########.fr       */
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

char *ft_quote_it(char *to_quote)
{
    char *quoted;
    char *tmp;
    char *tmp2;
    char **eq;

    eq = ft_split(to_quote, '=');
    tmp = ft_strdup(eq[1]);
    tmp2 = ft_strdup(eq[0]);
    ft_free_stringp(eq);
	tmp2 = ft_strjoin(ft_strdup("declare -x "), tmp2);
    quoted = ft_strjoin(tmp2, "="); /* tmp2 freed */
    tmp2 = tmp;
    tmp = ft_strjoin(ft_strdup("\""), tmp);
    tmp = ft_strjoin(tmp, "\"");
    quoted = ft_strjoin(quoted, tmp);
    free(tmp);
    free(tmp2);
    return (quoted);
}

t_env   *ft_set_export_lst(t_env *env_lst)
{
    t_env   *res;
    t_env   *toadd;
    char    *str;

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

char	**ft_export(t_init *init, char *str)
{
	char	**res;
	t_env	*head;
	t_env	*ev_var;

	if (!ft_is_exported(str))
		return (init->myenv);
	head = init->envlst;
	ev_var = ft_var_exist(init->envlst, str);
	if (ev_var)
		ft_edit_env_str(ev_var, str);
	else
		env_add_back(&init->envlst, new_env(str));
	init->envlst = head;
	res = ft_make_double_char(init->envlst);
	init->envlst = head;
	ft_free_stringp(init->myenv);
	return (res);
}
