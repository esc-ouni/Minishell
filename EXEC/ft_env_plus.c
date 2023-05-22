/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_plus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 01:01:15 by msamhaou          #+#    #+#             */
/*   Updated: 2023/05/22 02:45:36 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_make_double_char(t_env *env_lst)
{
	int		i;
	char	**res;

	i = ft_env_size(env_lst);
	res = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env_lst)
	{
	res[i] = ft_strdup(env_lst->str);
	i++;
	env_lst = env_lst->next;
	}
	res[i] = NULL;
	return (res);
}
