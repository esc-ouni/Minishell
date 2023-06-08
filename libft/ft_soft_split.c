/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_soft_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:48:49 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/08 14:50:05 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_soft_split_include(char *str, char c)
{
	char	**res;
	char	**tmp;
	int		trimlen;

	res = malloc(sizeof(char *) * 3);
	tmp = res;
	trimlen = ft_trim_len(str, c);
	*res = malloc(trimlen + 2);
	ft_strlcpy(*(res++), str, trimlen + 2);
	*(res++) = ft_substr(str, trimlen + 1, ft_strlen(str) - trimlen - 1);
	*res = NULL;
	return (tmp);
}

char	**ft_soft_split(char *str, char c)
{
	char	**res;
	char	**tmp;
	int		trimlen;

	res = malloc(sizeof(char *) * 3);
	tmp = res;
	trimlen = ft_trim_len(str, c);
	*res = malloc(trimlen + 1);
	ft_strlcpy(*(res++), str, trimlen + 1);
	*(res++) = ft_substr(str, trimlen + 1, ft_strlen(str) - trimlen - 1);
	*res = NULL;
	return (tmp);
}
