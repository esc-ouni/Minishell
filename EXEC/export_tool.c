/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 18:16:45 by msamhaou          #+#    #+#             */
/*   Updated: 2023/05/31 11:34:47 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_replace_exp_str(t_env *to_rep, char *str)
{
	free(to_rep->str);
	to_rep->str = ft_strdup(str);
}

int	ft_trim_len(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

int	ft_len_skip(char *str, char c)
{
	int	flag;
	int	i;

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
	int		flag;
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
	free(str);
	return (res);
}
