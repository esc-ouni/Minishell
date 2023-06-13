/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 15:47:14 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/13 22:39:03 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_atoi(const char *str)
{
	size_t				res;
	int					sign;

	res = 0;
	sign = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
	{
		sign *= -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		if (res == 922337203685477580 && sign == -1 && (*str - '0' == 8))
			return (0);
		res *= 10;
		res += *str - '0';
		if (res == 9223372036854775807 && sign == 1)
			return (res % 256);
		else if (res > 9223372036854775807 && (sign == 1 || sign == -1))
			return (-1);
		str++;
	}
	return (res * sign);
}
