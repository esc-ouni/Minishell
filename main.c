/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taha <taha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:37:31 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/04 17:18:47 by taha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	ft_init(int ac, char **av, char **ev, t_struct **cab)
{
	t_struct	*cable;

	(void)ac;
	(void)av;
	cable = (t_struct *)malloc(sizeof(t_struct));
	ft_set_env_lst(cable, ev);
	ft_env_set(cable);
	ft_exp_set(cable);
	cable->cmd = NULL;
	cable->friwi = NULL;
	cable->exit_val = 0;
	cable->var = 0;
	cable->is_heredoc = 0;
	cable->cmd_numb = 0;
	*cab = cable;
}

void	program(t_struct *cable)
{
	ft_exec(cable);
}

int	main(int ac, char **av, char **ev)
{
	t_struct	*cable;

	ft_init(ac, av, ev, &cable);
	// while (1)
	// 	program(cable);
	for(;cable->exp; cable->exp = cable->exp->next)
		printf("%s\n", cable->exp->str);
	return (0);
}
