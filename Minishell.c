/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 15:30:28 by idouni            #+#    #+#             */
/*   Updated: 2023/05/20 15:31:32 by idouni           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "Minishell.h"

int main(int argc, char **argv, char **env) 
{
    (void)argc;
    (void)argv;
    t_lexer		*h_lexer;
    t_collector	*collector;
    t_cmd		*cmd;
	t_env		*myenv_list;


	collector = NULL;
	myenv_list = NULL;
    while (1)
    {
        h_lexer = parser(&collector, &myenv_list);
        cmd = parser2(&collector, h_lexer);
        emplify(&collector, cmd, env);
        after_parse2(cmd);
		ft_collectorclear(&collector);
    }
    return 0;
}
