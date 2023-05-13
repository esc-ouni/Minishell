/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 14:31:25 by idouni            #+#    #+#             */
/*   Updated: 2022/11/12 14:31:28 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(t_collector **collector, char const *s, unsigned int start, size_t len)
{
	char	*ns;
	size_t	l;

	ns = NULL;
	if (s == NULL)
		return (NULL);
	if (start > (unsigned int)ft_strlen(s))
		return (ft_strdup(collector, ""));
	l = (unsigned int)ft_strlen(s + start);
	if (l < len)
		len = l;
	ns = (char *)h_malloc(collector, sizeof (char) * (len + 1), ns);
	if (!ns)
		return (NULL);
	ft_strlcpy(ns, s + start, len + 1);
	return (ns);
}
