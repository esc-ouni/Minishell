/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 12:34:14 by idouni            #+#    #+#             */
/*   Updated: 2023/05/22 16:31:59 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c <= 57 && c >= 48))
		return (1);
	else if ((c <= 90 && c >= 65) || (c <= 122 && c >= 97))
		return (1);
	else
		return (0);
}
