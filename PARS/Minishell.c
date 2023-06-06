/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:48:27 by idouni            #+#    #+#             */
/*   Updated: 2023/06/06 15:18:49 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init(int ac, char **av, char **ev, t_struct **cab)
{
	t_struct	*cable;

	(void)ac;
	(void)av;
	(void)ev;
	cable = (t_struct *)malloc(sizeof(t_struct));
	// ft_set_env_lst(cable, ev);
	// ft_env_set(cable);
	// ft_exp_set(cable);
	cable->cmd = NULL;
	cable->collector = malloc(sizeof(t_collector **));
	cable->collector[0] = NULL;
	cable->exit_val = 0;
	cable->var = 0;
	cable->is_heredoc = 0;
	cable->cmd_numb = 0;
	*cab = cable;
}

int main(int argc, char **argv, char **env) 
{
    t_cmd		*cmd;
	t_struct *cable;	

	cable = NULL;
	prm(argc, argv, env);
	ft_init(argc, argv,	env, &cable);
	strt(cable);
    while (1)
    {
		cmd = get_cmd(cable);
        // emplify(cable, cmd);
        after_parse2(cmd);
		ft_collectorclear(cable->collector, TMP);
    }
    return 0;
}
