/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:11:35 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/09 17:13:47 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_err(char *str, int type)
{
	ft_putstr_fd("exit: ", 2);
	if (type == 0)
		ft_putendl_fd("too many arguments", 2);
	if (type == 1)
	{
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": numeric argument required", 2);
	}
}

void	ft_print_var_err(char *str, int type)
{
	if (type == 0)
		ft_putstr_fd("export: `", 2);
	if (type == 1)
		ft_putstr_fd("unset: `", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}
