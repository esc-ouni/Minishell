/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:37:31 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/05 16:30:42 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	ft_init(t_collector **collector, int ac, char **av, char **ev, t_struct **cab)
{
	t_struct	*cable;

	(void)ac;
	(void)av;
	cable = NULL;
	cable = h_malloc(collector, sizeof(t_struct), cable, NTMP);
	cable->collector = collector;
	ft_set_env_lst(cable, ev);
	ft_env_set(cable);
	ft_exp_set(cable);
	cable->cmd = NULL;
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
	t_cmd 		*cmd;
	t_collector *collector;

	collector = NULL;
	ft_init(&collector, ac, av, ev, &cable);
	while (1)
	{
		cmd = get_cmd(cable);
		//exucution
		ft_collectorclear(cable->collector, TMP);
	}
	return (0);
}
