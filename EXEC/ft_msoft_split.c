/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_msoft_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:45:08 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/08 14:35:07 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_msoft_split_include(char *str, char c, t_struct *cable)
{
	char		**res;
	char		**tmp;
	int			trimlen;
	t_collector	**col;

	res = NULL;
	col = cable->collector;
	res = h_malloc(col, sizeof(char *) * 3, res, TMP);
	tmp = res;
	trimlen = ft_trim_len(str, c);
	*res = h_malloc(col, trimlen + 2, *res, TMP);
	ft_strlcpy(*res, str, trimlen + 2);
	res++;
	*(res++) = ft_msubstr(cable, str, trimlen + 1, \
			ft_strlen(str) - trimlen - 1);
	*res = NULL;
	return (tmp);
}
