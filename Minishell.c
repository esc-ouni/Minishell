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
    // s = malloc(100);
    printf("\n\t\t\tBIG_SHELL\n\n\n");
    while (1)
    {
        prompt();
        readline("");

        // stash = ft_split(s, ' ');
        // while (*stash)
        // {
        //     printf("%s\n", *stash);
        //     free(*stash);
        //     stash++;
        // }
        // s = malloc(100);
    }
    return 0;
}
