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
        write(1, "\x1B[34m", 6);
        s = readline("Your_prompt >> ");
        write(1, "\x1B[0m", 5   );

        stash = ft_split(s, ' ');
        while (*stash)
        {
            printf("%s\n", *stash);
            free(*stash);
            stash++;
        }
        // s = malloc(100);
    }
    return 0;
}
