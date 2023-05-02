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
    (void)head;
    t_cmd   *cmd;
    cmd = malloc(sizeof(t_cmd));
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
    printf("PART--1\n");
    while(node)
    {
        printf("=> node %d;\n", i);
        if (node->cmd)
            printf("   command : '%s'\n", node->cmd);
        printf("\n\n");
        i++;
        node = node->next;
    }
    printf("PART--2\n");
    after_parse2(parser2(head));
}

void    after_parse2(t_cmd  *cmd)
{
    int i = 0;
    int i2 = 0;
    t_cmd  *node;
    (void)cmd;
    char **s;
    s = ft_split(ft_strdup("ls -la -op"), ' ');
    node = malloc(sizeof(t_cmd));
    node->cmd = s;
    node->out_files = malloc(sizeof(t_file));
    node->in_files = malloc(sizeof(t_file));
    node->out_files->filename = ft_strdup("hello");
    node->out_files->next = NULL;
    node->in_files->filename = ft_strdup("hello");
    node->in_files->next = NULL;
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
        // debug();
        if (node->out_files->filename)
        {
            while(node->out_files->filename)
            {
                printf("%s", node->out_files->filename);
                node->out_files = node->out_files->next;
            }
        }
        printf("\n");
        printf("   in_files    : ");
        if(node->in_files->filename)
        {
            while(node->in_files->filename)
            {
                printf("%s", node->in_files->filename);
                node->in_files = node->in_files->next;
            }
        }
        printf("\n");
        printf("\n");
        i++;
        node = node->next;
    }
	// ft_lstclear(&cmd);
}
