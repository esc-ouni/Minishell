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

void    after_parse(t_list  *head)
{
    t_list  *node;
    char    **str;
    int i = 1;
    int i2 = 0;

    node = head;
    str = malloc(sizeof(char *) + 10);
    printf("\n");
    while(node)
    {
        strcpy(str[i2], node->cmd);
        printf("=> node %d;\n", i);
        printf("   command : %s\n", node->cmd);
        printf("   type    : %d", node->type);
        printf("\n\n");
        i++;
        i2++;
        node = node->next;
    }
    str[i2] = NULL;
	// ft_lstclear(&head);
}
