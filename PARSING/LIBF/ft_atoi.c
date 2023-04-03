/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 12:33:14 by idouni            #+#    #+#             */
/*   Updated: 2022/11/12 14:45:24 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long long	check(unsigned long long nb, int s)
{
	if (nb >= 9223372036854775807 && s == 1)
		return (-1);
	else if (nb > 9223372036854775807 && s == -1)
		return (0);
	return (nb);
}

int	ft_atoi(const char *str)
{
	int					i;
	unsigned long long	r;
	int					s;

	s = 1;
	r = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	while ((str[i] == 45 || str[i] == 43))
	{
		if (str[i] == 45)
			s *= -1;
		i++;
		if ((str[i] < 48 || str[i] > 57))
			return (0);
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		r = r * 10 + (str[i] - 48);
		i++;
	}
	r = (unsigned)check(r, s);
	return (r * s);
}
