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

int main() 
{
    // t_list  *n;
    // char    **s;
    // s = malloc(8 * 4);
    // s[0] = malloc(8 * 10);
    // s[1] = malloc(8 * 10);
    // s[2] = malloc(8 * 10);
    // s[3] = NULL;
    // strcpy(s[0], "grep");
    // strcpy(s[1], "\"me");
    // strcpy(s[2], "hello\"");
    start();
    while (1)
    {
        prompt();
        after_parse(parser());
        // execve("/usr/bin/grep", s,NULL);
        // system(n->cmd);
    }
    // free(s[0]);
    // free(s[1]);
    // free(s[2]);
    // free(s[3]);
    // free(s);
    return 0;
}
