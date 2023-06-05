/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:37:31 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/05 16:55:02 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

// void	ft_init(t_collector **collector, char **ev, t_struct **cab)
// {
// 	t_struct	*cable;

// 	cable = NULL;
// 	cable = h_malloc(collector, sizeof(t_struct), cable, NTMP);
// 	cable->collector = collector;
// 	ft_set_env_lst(cable, ev);
// 	ft_env_set(cable);
// 	ft_exp_set(cable);
// 	cable->cmd = NULL;
// 	cable->exit_val = 0;
// 	cable->var = 0;
// 	cable->is_heredoc = 0;
// 	cable->cmd_numb = 0;
// 	*cab = cable;
// }

void	ft_init(char **ev, t_struct **cab)
{
	t_struct	*cable;
	static t_collector *collector;

	collector = NULL;
	cable = NULL;
	cable = h_malloc(&collector, sizeof(t_struct), cable, NTMP);
	cable->collector = &collector;
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

void prm(int argc, char **argv, char **env)
{
	(void)argv;
	
	if (argc == 2)
	{
		execve("/bin/bash", argv, env);
		exit(0);
	}
	else if(argc > 1)
		exit(0);
}

void	program(t_struct *cable)
{
	ft_exec(cable);
}

int	main(int ac, char **av, char **ev)
{
	t_struct	*cable;
	t_cmd 		*cmd;

	prm(ac, av, ev);
	ft_init(ev, &cable);
	while (1)
	{
		cmd = get_cmd(cable);
		//exucution
		ft_collectorclear(cable->collector, TMP);
	}
	return (0);
}
