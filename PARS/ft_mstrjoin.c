/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mstrjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 14:28:42 by idouni            #+#    #+#             */
/*   Updated: 2022/11/12 14:28:44 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_mstrjoin(t_collector **collector, char const *s1, char const *s2)
{
	size_t		l1;
	size_t		l2;
	char		*ns;

	ns = NULL;
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	ns = (char *)h_malloc(collector, sizeof(char) * (l1 + l2 + 1), ns);
	if (ns)
	{
		if (s1)
			ft_memmove(ns, s1, l1);
		if (s2)
			ft_memmove(ns + l1, s2, l2);
		ns[l2 + l1] = '\0';
		return (ns);
	}
	return (ns);
}
