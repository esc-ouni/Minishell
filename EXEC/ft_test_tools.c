/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 08:47:21 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/06 08:49:25 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_envlst(t_envlst *envlst)
{
	while (envlst)
	{
		printf("%s\n", envlst->str);
		envlst = envlst->next;
	}
}

void	ft_print_exp(t_exp *exp)
{
	while (exp)
	{
		printf("%s\n", exp->str);
		exp = exp->next;
	}
}
