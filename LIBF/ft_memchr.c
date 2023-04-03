/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 12:58:11 by idouni            #+#    #+#             */
/*   Updated: 2022/11/12 12:58:14 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t					i;
	const unsigned char		*p_s;

	i = 0;
	p_s = (const unsigned char *)s;
	while (n)
	{
		if (p_s[i] == (unsigned char)c)
			return ((void *)s + i);
		i++;
		n--;
	}
	return (0);
}
