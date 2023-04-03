/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 14:30:56 by idouni            #+#    #+#             */
/*   Updated: 2022/11/12 14:30:58 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	l;

	l = ft_strlen(s);
	while (l)
	{
		if (s[l] == (unsigned char)c)
			return ((char *)s + l);
		l--;
	}
	if (s[l] == (unsigned char)c)
		return ((char *)s);
	return (0);
}
