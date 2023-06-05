/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exp_lst_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 11:46:53 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/05 12:27:36 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_valid_var(const char	*str)
{
	char	*pstr;

	pstr = (char *)str;
	if (*pstr == '=' || *pstr == '+')
		return (0);
	while (*pstr && *pstr != '=')
	{
		if (((*pstr == '+') && (*(pstr + 1) != '=')) \
		&& (!ft_isalnum(*pstr) || *pstr != '_'))
			return (0);
		pstr++;
	}
	return (1);
}

// t_envlst	*ft_var_env_exist(t_envlst *envlst, char *str)
// {
// 	char	**var;

// 	var = ft_soft_split(str, '=');
// 	while (envlst)
// 	{
// 		if (!ft_strcmp(envlst->str, var[0]))
// 		{

// 			return (envlst);
// 		}
// 		envlst = envlst->next;
// 	}
// 	ft_free_stringp(var);
// 	return (NULL);
// }

t_exp	*ft_exp_new_node(char *str)
{
	t_exp	*node;

	node = (t_exp *)malloc(sizeof(t_exp));
	node->str = ft_strdup(str);
	node->next = NULL;
	return (node);
}

t_exp	*ft_last_explst(t_exp *envlst)
{
	while (envlst->next)
		envlst = envlst->next;
	return (envlst);
}

void	ft_exp_add_back(t_exp **envlst, t_exp *toadd)
{
	if (!*envlst)
		*envlst = toadd;
	else
		ft_last_explst(*envlst)->next = toadd;
}
