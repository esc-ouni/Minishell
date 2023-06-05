/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:37:31 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/05 12:16:31 by idouni           ###   ########.fr       */
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
	cable->collector = malloc(sizeof(t_collector **));
	cable->collector[0] = NULL;
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
	while (1)
		program(cable);
	return (0);
}
