/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 14:25:30 by idouni            #+#    #+#             */
/*   Updated: 2022/11/12 14:25:32 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char			*p_d;
	const char		*p_s;

	if (!src && !dst)
		return (0);
	if (len == 0)
		return (dst);
	p_d = (char *)dst;
	p_s = (const char *)src;
	if (dst > src)
	{
		p_d = (char *)dst + (len - 1);
		p_s = (const char *)src + (len - 1);
		while (len)
		{
			*p_d-- = *p_s--;
			len--;
		}
	}
	else
		ft_memcpy(p_d, p_s, len);
	return (dst);
}
