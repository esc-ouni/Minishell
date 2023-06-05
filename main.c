/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:37:31 by msamhaou          #+#    #+#             */

/*   Updated: 2023/06/05 12:54:54 by msamhaou         ###   ########.fr       */

/*   Updated: 2023/06/05 16:56:06 by idouni           ###   ########.fr       */

/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"

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
	t_cmd 		*cmd;

	atexit(foo);
	prm(ac, av, ev);
	ft_init(ev, &cable);
	for (; cable->exp; cable->exp=cable->exp->next)
		printf("%s\n", cable->exp->str);
	ft_collectorclear(cable->collector, NTMP);
	return (0);

}
