/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:13:06 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/06 10:55:20 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_len_skip(char *str, char c)
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

char	*ft_trim_char(char *str, char c, t_struct *cable)
{
	int		trim_len;
	int		j;
	int		k;
	int		flag;
	char	*res;

	trim_len = ft_len_skip(str, c);
	res = h_malloc(cable->collector,sizeof(char) * trim_len + 1, res, NTMP);
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
