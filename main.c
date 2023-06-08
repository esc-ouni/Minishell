/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:37:31 by msamhaou          #+#    #+#             */

/*   Updated: 2023/06/05 16:56:06 by idouni           ###   ########.fr       */

/*   Updated: 2023/06/05 12:54:54 by msamhaou         ###   ########.fr       */

/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init(char **ev, t_struct **cab)
{
	t_struct	*cable;
	static t_collector	*collector;

	collector = NULL;
	cable = NULL;
	cable = h_malloc(&collector, sizeof(t_struct), cable, NTMP);
	cable->collector = &collector;
	ft_set_env_lst(cable, ev);
	ft_exp_set(cable);
	ft_unset(cable, "OLDPWD");
	ft_export_exp(cable, "OLDPWD");
	cable->cmd = NULL;
	cable->exit_val = 0;
	// cable->var = 0;
	cable->is_heredoc = 0;
	cable->cmd_numb = 0;
	cable->tmp_fd_in = dup(0);
	cable->tmp_fd_out = dup(1);
	*cab = cable;
}

void	program(t_struct *cable)
{
	ft_env_set(cable);
	dup2(cable->tmp_fd_in, 0);
	cable->cmd = get_cmd(cable);
	// after_parse2(cable->cmd);
	//exucution
	g_var = 0;
	ft_exec(cable);
	g_var = 1;
	ft_collectorclear(cable->collector, TMP);
}

void	foo()
{
	system("leaks minishell");
}

int	main(int ac, char **av, char **ev)
{
	t_struct	*cable;

	// atexit(foo);
	g_var = 1;
	prm(ac, av, ev);
	ft_init(ev, &cable);
	strt(cable);
	while (1)
		program(cable);
}
