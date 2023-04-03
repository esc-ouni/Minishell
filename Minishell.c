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
    char    *s;
    char    **stash;
    t_list  **head;

    head = NULL;
    s = malloc(100);
    printf("\n\t\t\tBIG_SHELL\n\n\n");
    while (1)
    {
        printf("\x1B[34m");
        s = readline("Your_prompt >> ");

        // printf("%s\n", s);
        printf("\x1B[0m");
        // free(s);
        stash = ft_split(s, ' ');
        while (*stash)
        {
            printf("%s\n", *stash);
            stash++;
        }
        // s = malloc(100);
    }
    return 0;
}
