/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdigit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:11:18 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/09 17:14:53 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strdigit(const char *str)
{
	char	*s;

	s = (char *)str;
	while (*s)
		if (!ft_isdigit(*s++))
			return (0);
	return (1);
}
