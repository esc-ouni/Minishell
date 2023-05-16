/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 14:30:39 by idouni            #+#    #+#             */
/*   Updated: 2022/11/12 14:30:42 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	if (!haystack && len == 0)
		return (NULL);
	if (needle[i] == '\0')
		return ((char *)haystack);
	while (haystack[i] != '\0')
	{
		while (haystack[i + n] == needle[n] || needle[n] == '\0')
		{
			if (n + i > len)
				return (0);
			else if (needle[n] == '\0')
				return ((char *)haystack + i);
			n++;
		}
		n = 0;
		i++;
	}
	return (0);
}
