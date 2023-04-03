/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 12:58:57 by idouni            #+#    #+#             */
/*   Updated: 2022/11/12 12:59:00 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*p_d;
	const unsigned char	*p_s;

	if (!dst && !src)
		return (0);
	i = 0;
	p_d = (unsigned char *)dst;
	p_s = (unsigned char *)src;
	while (n)
	{
		p_d[i] = p_s[i];
		i++;
		n--;
	}
	return (p_d);
}
