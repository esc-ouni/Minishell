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


// printf("###########");
// printf("#         #");
// printf("#         #");
// printf("#  #####  #");
// printf("#  #####  #");
// printf("#         #");
// printf("#         #");
// printf("###########");
int main() 
{
    printf("\n\t\t\tBIG_SHELL\n\n\n");
    while (1) {
        char s[100];
        printf("\x1B[34m");
        printf("Your_prompt >> ");
        printf("\x1B[0m");
        scanf("%s", s);
    }
    return 0;
}