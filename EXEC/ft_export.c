/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 01:03:14 by msamhaou          #+#    #+#             */
/*   Updated: 2023/05/27 15:45:54 by msamhaou         ###   ########.fr       */
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

char	*ft_quote_one(char *str)
{
	char	*quoted;

	quoted = ft_strjoin(ft_strdup("declare -x "), str);
	quoted = ft_strjoin(quoted, "\"\"");
	return (quoted);
}

char	*ft_quote_two(char	**eq)
{
	char	*tmp;
	char	*tmp2;
	char	*quoted;

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

void	ft_plus_eq_check(char	**str, t_env *env)
{
	t_env	*exist;
	char *trimmed;

	exist = NULL;
	if (ft_strnstr(*str, "+=", ft_strlen(*str)))
	{
		*str = ft_trim_char(*str, '+');
		exist = ft_var_exist(env, *str);
		if (exist)
			*str = ft_strjoin(*str, ft_split(*str, '=')[1]);
	}
}

char *ft_quote_it(char *to_quote)
{
    char *quoted;
    char **eq;

	if (ft_strchr(to_quote, '='))
	{
		eq = ft_split(to_quote, '=');
		if (!eq[1])
			return (quoted = ft_quote_one(to_quote));
		else
			quoted = ft_quote_two(eq);
	}
	else
	{
		quoted = ft_strjoin(ft_strdup("declare -x "), to_quote);
	}

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

int	ft_trim_len(const char *str, char c)
{
	int	i;

	i= 0;
	while(str[i] && str[i] != c)
		i++;
	return (i);
}

int	ft_len_skip(char *str, char c)
{
	int	flag;
	int	i;;

	flag = 0;
	i = 0;
	while (*str)
	{
		if (*str == c && !flag)
			str++;
		if (!(*str))
			break ;
		i++;
		str++;
	}
	return (i);
}

char	*ft_trim_char(char *str, char c)
{
	int		trim_len;
	int		j;
	int		k;
	int	flag;
	char	*res;

	trim_len = ft_len_skip(str, c);
	res = malloc(sizeof(char) * trim_len + 1);
	j = 0;
	k = 0;
	flag = 0;
	while (str[k])
	{
		if ((str[k] == c) && !flag)
		{
			flag = 1;
			k++;
		}
		if (!str[k])
			break ;
		res[j++] = str[k++];
	}
	res[j] = '\0';
	return (res);
}

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
		sub_origin = ft_substr(exp->str, start_len, trim_len - ft_strlen("declare -x "));
		if (ft_strcmp(sub_origin, sub_tocmp) == 0)
			return (free(sub_tocmp), free(sub_origin), exp);
		free(sub_origin);
		exp = exp->next;
	}
	return(free(sub_tocmp), NULL);
}

void	ft_replace_exp_str(t_env *to_rep, char *str)
{
	free(to_rep->str);
	to_rep->str = ft_strdup(str);
}

void	ft_exp_add_back(t_env **env, char *str)
{
	char	*quoted;
	t_env	*exist;

	exist = ft_exp_var_exist(*env, str);
	if (exist)
		ft_replace_exp_str(exist, str);
	quoted = ft_quote_it(str);
	env_add_back(env, new_env(quoted));
	ft_sort_env(*env);
}

char	**ft_export(t_init *init, char *str)
{
	char	**res;
	t_env	*head;
	t_env	*ev_var;

	head = init->envlst;
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
