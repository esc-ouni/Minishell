/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 14:25:47 by idouni            #+#    #+#             */
/*   Updated: 2022/11/12 14:25:49 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*s;
	int				i;

	i = 0;
	s = (unsigned char *)b;
	while (len)
	{
		s[i] = (unsigned char)c;
		len--;
		i++;
	}
	return (b);
}
