/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 20:55:08 by idouni            #+#    #+#             */
/*   Updated: 2023/04/02 20:55:34 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int main() 
{
    start();
    while (1)
    {
        prompt();
        readline("");
        after_parse();
    }
    return 0;
}

void    after_parse(t_list  **head)
{
    t_list  *node;
    int i = 0;

    node = *head;
    while(node)
    {
        printf("node %d\n", i);
        printf("command   : %s", node->cmd);
        printf("tar. file : %s", node->target);
        printf("\n\n");
        i++;
        node = node->next;
    }
}