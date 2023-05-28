/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:48:27 by idouni            #+#    #+#             */
/*   Updated: 2023/05/28 15:29:25 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **env) 
{
    (void)env;
    (void)argc;
    (void)argv;
	char		*s;
    t_lexer		*h_lexer;
    t_collector	*collector;
    t_cmd		*cmd;


	collector = NULL;
    while (1)
    {
		s = prompt();
        h_lexer = parser(&collector, NULL, s);
        cmd = parser2(&collector, h_lexer);
        emplify(&collector, cmd);
        after_parse2(cmd);
		ft_collectorclear(&collector);
		system("leaks Minishell");
    }
    return 0;
}
