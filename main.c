/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:37:31 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/05 14:10:35 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	ft_init(int ac, char **av, char **ev, t_struct **cab)
{
	t_struct	*cable;
	t_collector *collector;

	(void)ac;
	(void)av;
	collector = NULL;
	cable = NULL;
	cable = (t_struct *)h_malloc(&collector, sizeof(t_struct), cable, NTMP);
	cable->cmd = NULL;
	cable->collector = NULL;
	cable->collector = h_malloc(&collector, sizeof(t_collector **), cable->collector, NTMP);
	cable->collector = &collector;
	cable->exit_val = 0;
	cable->var = 0;
	cable->is_heredoc = 0;
	cable->cmd_numb = 0;
	ft_set_env_lst(cable, ev);
	ft_env_set(cable);
	ft_exp_set(cable);
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
