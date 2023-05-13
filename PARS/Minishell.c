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
t_collector **collect_head = NULL;

void h_free_all(t_collector **collect_head)
{
    t_collector *current = *collect_head;
    t_collector *next;
    while (current)
    {
        next = current->next;
        free(current->addr);
        free(current);
        current = next;
		printf("DONE\n");
    }
    *collect_head = NULL; // Reset the head pointer to NULL
}

int main(int argc, char **argv, char **env) 
{
    (void)argc;
    (void)argv;
    t_lexer		*h_lexer;
    t_collector	*collector;
    t_cmd		*cmd;

	collector = NULL;
    // start();
    while (1)
    {
        h_lexer = parser(&collector);
        cmd = parser2(&collector, h_lexer);
        emplify(cmd, env);
        after_parse2(cmd);
		h_free_all(&collector);
    }
    return 0;
}
