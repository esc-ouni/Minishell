/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:37:31 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/02 15:41:45 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	ft_init(int ac, char **av, char **ev, t_struct **cable)
{
	(void)ac;
	(void)av;
	*cable = (t_struct *)malloc(sizeof(t_struct));
	ft_env_set(*cable, ev);
}

void	program(t_struct *cable)
{

}

int	main(int ac, char **av, char **ev)
{
	t_struct	*cable;
	ft_init(ac, av, ev, &cable);
	while (1)
		program(cable);
}
