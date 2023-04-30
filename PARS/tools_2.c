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
    int i;
    int i2;
    t_list  *n;
    t_cmd   *cmd;
    t_file  *out_files;

    i = 0;
    i2 = 0;
    n = head;
    cmd = malloc(2 * sizeof(t_cmd));
    char **str;
    // char *s;
    out_files = malloc(sizeof(t_file *) * 2);
    out_files = NULL;
    cmd->cmd = malloc(sizeof(char *) * 10);
    while (n)
    {
        cmd = malloc(sizeof(t_cmd));
        str = ft_split(n->cmd, ' ');
        while (str[i])
        {
            if (!strcmp(str[i], ">"))
            {
                out_files->filename = strdup(str[i + 1]);
            }
            i++;
        }
        i = 0;
        while (str[i] && str[i - 1])
        {
            if (!strcmp(str[i], ">"))
                i += 1;
            else
            {
                cmd->cmd[i2] = strdup(str[i]);
                i2++;
                cmd->cmd[i2] = NULL;
            }
            i++;
        }
        n = n->next;
    }
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
    if (check_syntax(s))
        return (NULL);
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
    // parser2(head);
	return (head);
}

void    after_parse(t_list  *head)
{
    int i = 0;
    t_list  *node;
    t_list  *node2;

    node = head;
    node2 = head;
    while(node)
    {
        printf("=> node %d;\n", i);
        printf("   command : %s\n", node->cmd);
        printf("   type    : %d", node->type);
        printf("\n\n");
        i++;
        node = node->next;
    }
    after_parse2(parser2(head));
	// ft_lstclear(&head);
}

void    after_parse2(t_cmd  *cmd)
{
    int i = 0;
    t_cmd  *node;

    node = cmd;
    // while(node)
    // {
    printf("=> node %d;\n", i);
    printf("   command   : %s\n", node->cmd[0]);
    printf("   command   : %s\n", node->cmd[1]);
    printf("   out_files : %s\n", node->out_files->filename);
    printf("\n\n");
    i++;
        // node = node->next;
    // }
	// ft_lstclear(&cmd);
}

int    check_syntax(char *s)
{
    int i;
    int dq;

    i = 0;
    dq = 0;
    while (s[i])
    {
        if (s[i] == '"')
            dq++;
        i++;
    }
    if (dq % 2)
    {
        printf("Minishell: syntax error");
        return (1);
    }
    return (0);
}
