/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 14:11:50 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/05 16:19:29 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init(t_collector **collector, int ac, char **av, char **ev, t_struct **cab)
{
	t_struct	*cable;

	(void)ac;
	(void)av;
	cable = NULL;
	cable->collector = collector;
	cable = (t_struct *)h_malloc(cable->collector, sizeof(t_struct), cable, NTMP);
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

void	foo()
{
	system("leaks minishell");
}
int	main(int ac, char **av, char **ev)
{
	t_struct	*cable;
	t_collector	*colect;

	atexit(foo);
	ft_init(&colect, ac, av, ev, &cable);

	ft_export_exp(cable, "LOLHI");
	for(; cable->exp; cable->exp = cable->exp->next)
		printf("%s\n", cable->exp->str);
	ft_collectorclear(cable->collector, ALL);
}
