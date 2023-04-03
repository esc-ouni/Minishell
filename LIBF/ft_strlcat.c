/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 14:28:59 by idouni            #+#    #+#             */
/*   Updated: 2022/11/12 16:26:08 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	d_l;
	size_t	s_l;
	size_t	i;

	i = 0;
	if (!dst && dstsize == 0)
		return (0);
	d_l = ft_strlen(dst);
	s_l = ft_strlen(src);
	if (dstsize <= d_l)
		return (dstsize + s_l);
	while (src[i] && (d_l + i < dstsize - 1))
	{
		dst[d_l + i] = src[i];
		i++;
	}
	dst[d_l + i] = '\0';
	return (d_l + s_l);
}
