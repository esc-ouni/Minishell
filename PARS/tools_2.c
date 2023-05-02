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
    t_file  *ot_fil;

    i = 0;
    i2 = 0;
    n = head;
    out_files = malloc(sizeof(t_file));
    ot_fil = out_files;
    cmd = malloc(sizeof(t_cmd));
    cmd->cmd = malloc(sizeof (char *) * 10);
    while (n)
    {
        cmd->cmd = ft_split(n->cmd, ' ');
        // cmd->cmd[i] = strdup(n->cmd);
        // cmd->cmd[i + 1] = NULL; 
        // cmd = cmd->next;
        n = n->next;
        i++;
    }
    i = 0;
    char **s = calloc(2 , sizeof (char *));
    // char *s = calloc(10 , sizeof (char));
    while (cmd->cmd[i])
    {
        if (!strcmp(cmd->cmd[i], ">"))
        {
            i++;
            out_files->filename = ft_strdup(cmd->cmd[i]);
            out_files = out_files->next;
            out_files = malloc(sizeof(t_file));
            out_files = NULL;
        }
        else
        {
            s[i2] = ft_strdup(cmd->cmd[i]);
            printf("%s ", s[i2]);
        }
            // s[i2] = ft_strjoin(ft_strjoin(s, strdup(" ")), cmd->cmd[i]);
        i++;
        i2++;
    }
    printf("\n\n");
    // printf("%s\n", s);
    cmd->cmd = s;
    cmd->out_files = ot_fil;
    cmd->next = NULL;
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
    // if (check_syntax(s))
    //     return (NULL);
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
    after_parse2(parser2(node2));
	// ft_lstclear(&head);
}

void    after_parse2(t_cmd  *cmd)
{
    int i = 0;
    t_cmd  *node;

    node = cmd;
    while(node)
    {
        // printf("=> node %d;\n", i);
        // printf("   command   : %s\n", node->cmd[0]);
        printf("   out_files : %s", node->out_files->filename);
        printf("\n\n");
        i++;
        node = node->next;
    }
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
