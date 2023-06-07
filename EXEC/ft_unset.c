/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 12:17:57 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/07 14:20:52 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_valid_unset(const char *str)
{
	char	*s;

	s = (char *)str;
	while (*s)
	{
		if (!ft_isalnum(*s) && *s != '_')
			return (0);
		s++;
	}
	return (1);
}

void	ft_unset(t_struct *cable, char *str)
{
	if (!ft_valid_unset(str))
		return (ft_print_var_err(str, 1));
	ft_unset_envlst(cable, str);
	ft_unset_exp(cable, str);
}
