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
    start();
    while (1)
    {
        prompt();
        after_parse(parser());
        // execve("/bin/ls",&n->cmd, NULL);
        // system(n->cmd);
    }
    return 0;
}


void    full(t_list **fuck)
{

}


int main(void)
{
    t_f_list *p;

    p = NULL;
    full(&p);
}