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
    t_cmd *cmd;
    t_cmd *n_cmd;
    char **menv;

    menv = mgetenv(env);
    // start();
    while (1)
    {
        prompt();
        h_lexer = parser();
        cmd = parser2(h_lexer);
        n_cmd = cmd;
        while (n_cmd)
        {
            n_cmd->env = menv;
            n_cmd = n_cmd->next;
        }
        after_parse2(cmd); // hide this
    }
    return 0;
}
