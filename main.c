/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taha <taha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:37:31 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/04 16:04:28 by taha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init(int ac, char **av, char **ev, t_struct **cable)
{
	(void)ac;
	(void)av;
	*cable = (t_struct *)malloc(sizeof(t_struct));

}

void	program(t_struct *cable)
{

}

int	main(int ac, char **av, char **ev)
{
	char	*lol= ft_strdup("hi");
	printf("%s\n", lol);
	return (0);
}
