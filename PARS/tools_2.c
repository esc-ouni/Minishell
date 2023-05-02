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

t_cmd  *parser2(t_list *head)
{
    t_list  *node;
    t_cmd   *cmd;

    node = head;
    cmd = malloc(sizeof(t_cmd));
    cmd = NULL;
    // while (node)
    // {
        // node->
    // }
    return (cmd);
}

t_list  *parser()
{
	int		i = 0;
    char    *s;
    char    **str;
	t_list	*head;

	head = NULL;
    s = readline(" ");
	str = ft_split(s, '|');
	while (str[i])
	{
		ft_lstadd_back(&head, ft_lstnew(ft_strtrim(str[i], " ")));
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
    int i = 0;
    t_list  *node;

    node = head;
    printf("\x1B[32m");
    printf("PART--1:\n");
	printf("\x1B[0m");
    while(node)
    {
        printf("=> node %d;\n", i);
        if (node->cmd)
            printf("   command : '%s'\n", node->cmd);
        printf("\n\n");
        i++;
        node = node->next;
    }
    printf("\x1B[32m");
    printf("PART--2:\n");
	printf("\x1B[0m");
    after_parse2(parser2(head));
}

void    after_parse2(t_cmd  *cmd)
{
    int i = 0;
    int i2 = 0;
    t_cmd  *node;

    node = cmd;
    while(node)
    {
        printf("=> t_cmd %d;\n", i);
        printf("   command     : ");
        while(node->cmd[i2])
        {
            printf("%s ", node->cmd[i2]);
            i2++;
        }
        i2 = 0;
        printf("\n");
        printf("   out_files   : ");
        while(node->out_files)
        {
            printf("%s ", node->out_files->filename);
            node->out_files = node->out_files->next;
        }
        printf("\n");
        printf("   in_files    : ");
        while(node->in_files)
        {
            printf("%s ", node->in_files->filename);
            node->in_files = node->in_files->next;
        }
        printf("\n\n");
        i++;
        node = node->next;
    }
	// ft_lstclear(&cmd);
}
