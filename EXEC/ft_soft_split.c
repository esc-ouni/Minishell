/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_soft_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:48:49 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/08 16:21:09 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_soft_split(char *str, char c, t_struct *cable)
{
	char	**res;
	char	**tmp;
	int		trimlen;

	res = NULL;
	res = h_malloc(cable->collector, sizeof(char *) * 3, res, TMP);
	tmp = res;
	trimlen = ft_trim_len(str, c);
	*res = h_malloc(cable->collector, trimlen + 1, *res, TMP);
	ft_strlcpy(*(res++), str, trimlen + 1);
	*(res) = ft_msubstr(cable, str, trimlen + 1, ft_strlen(str) - trimlen - 1);
	res++;
	*res = NULL;
	return (tmp);
}
