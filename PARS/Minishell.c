/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 20:55:08 by idouni            #+#    #+#             */
/*   Updated: 2023/04/04 18:45:33 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int main(int argc, char **argv, char **env) 
{
    (void)argc;
    (void)argv;
    t_lexer  *h_lexer;
    t_cmd    *cmd;

    start();
    while (1)
    {
        h_lexer = parser();
        cmd = parser2(h_lexer);
        emplify(cmd, env);
        after_parse2(cmd);
    }
    return 0;
}
