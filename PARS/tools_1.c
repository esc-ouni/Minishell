/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:32:34 by idouni            #+#    #+#             */
/*   Updated: 2023/04/04 14:32:56 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"


void	check_type(t_list	*node)
{
	if (!ft_strncmp(node->cmd, "|", 1))
		node->type = PIP;
	else if (!ft_strncmp(node->cmd, ";", 1))
		node->type = ERR;
	else if (!ft_strncmp(node->cmd, ">", 1))
		node->type = RED;
    else if (!ft_strncmp(node->cmd, ">>", 1))
		node->type = RED;
    else if (!ft_strncmp(node->cmd, "<", 1))
		node->type = RED;
    else if (!ft_strncmp(node->cmd, "<<", 1))
		node->type = RED;
	else if (!ft_strncmp(node->cmd, "\'", 1))
		node->type = SQU;
	else if (!ft_strncmp(node->cmd, "\"", 1))
		node->type = DQU;
}

void    prompt()
{
    printf("\x1B[34m");
    printf("\nBig_shell >> ");
    printf("\x1B[0m");
}

void    start()
{
    char    *s;
    int     fd;

    fd = open("header.h", O_RDONLY);
    printf("\x1B[32m");
    while ((s = get_next_line(fd)))
	{
        printf("%s", s);
		free(s);
	}
    printf("\x1B[0m");
    printf("\n\n");
    close(fd);
}

// void	*h_malloc(t_data data, size_t s, void *p)
// {
// 	p = malloc(s);
// 	if (!p)
// 	{
// 		ft_exit_with_error(data);
// 	}
// 	return (p);
// }