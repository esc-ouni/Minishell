/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:33:03 by idouni            #+#    #+#             */
/*   Updated: 2023/04/04 14:33:28 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void    after_parse(t_list  *head)
{
    t_list  *node;
    int i = 1;

    node = head;
    printf("\n");
    while(node)
    {
        printf("=> node %d;\n", i);
        printf("   command : %s\n", node->cmd);
        printf("   type    : %d", node->type);
        printf("\n\n");
        i++;
        node = node->next;
    }
	ft_lstclear(&head);
}

t_list  *read_line()
{
	int		i = 0;
    char    *s;
    char    **str;
	t_list	*head;

	head = NULL;
    s = readline(" ");
	str = ft_split(s, ' ');
	while (str[i])
	{
		ft_lstadd_back(&head, ft_lstnew(str[i]));
		free(str[i]);
		i++;
	}
	free(str[i]);
	free(str);
	free(s);
	return (head);
}