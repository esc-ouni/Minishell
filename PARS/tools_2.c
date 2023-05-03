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
    char    **full_cmd;
    t_file  *out_files;
    t_file  *in_files;
    t_list  *node;
    t_list  **tmp;
    t_list  *tmp_n;
    t_list  *n;
    t_cmd   *cmd;
    int i = 0;
    int l;

    char **s;
    tmp = NULL;

    node = head;
    full_cmd = malloc(sizeof(char *) * 15);
    cmd = NULL;
    out_files = NULL;
    in_files = NULL;
    while (node)
    {
        s = ft_split(node->cmd, ' ');
        tmp_n = ft_lstnew(*s);
        tmp = &tmp_n;
        s++;
        while(*s)
        {
            ft_lstadd_back(tmp, ft_lstnew(*s));
            s++;
        }
        // CHECK_FOR_OUT_FILES
        n = *tmp;
        while (n)
        {
            if (!strcmp(n->cmd, ">"))
            {
                n = n->next;
                add_file_node(&out_files, n->cmd, O_TRUNC);
            }
            if (!strcmp(n->cmd, ">>"))
            {
                n = n->next;
                add_file_node(&out_files, n->cmd, O_APPEND);
            }
            n = n->next;
        }
        // printf("\nout_files :\n");
        // while (out_files)
        // {
        //     printf("  > %s\n", out_files->filename);
        //     out_files = out_files->next;
        // }

        // CHECK_FOR_IN_FILES
        n = *tmp;
        while (n)
        {
            if (!strcmp(n->cmd, "<"))
            {
                n = n->next;
                add_file_node(&in_files, n->cmd, O_TRUNC);
            }
            if (!strcmp(n->cmd, "<<"))
            {
                n = n->next;
                add_file_node(&in_files, n->cmd, O_TRUNC);
            }
            n = n->next;
        }
        // printf("\nin_files :\n\n");
        // while (in_files)
        // {
        //     printf("  > %s\n", in_files->filename);
        //     in_files = in_files->next;
        // }

        // GET_FULL_CMD
        n = *tmp;
        while (n)
        {
            if (!strcmp(n->cmd, "<") || !strcmp(n->cmd, "<<") || !strcmp(n->cmd, ">") || !strcmp(n->cmd, ">>"))
                n = n->next;
            else
            {
                full_cmd[i] = ft_strdup(n->cmd);
                full_cmd[i + 1] = NULL;
                i++;
            }
            n = n->next;
        }
        i = 0;
        // printf("\nfull_cmd :\n\n");
        // while (full_cmd[i])
        // {
        //     printf("  > %s\n", full_cmd[i]);
        //     i++;
        // }
        // printf("\n");
        // printf("\n");
        i = 0;
        add_to_cmd(&cmd, full_cmd, out_files, in_files);
        full_cmd[0] = NULL;
        out_files = NULL;
        in_files = NULL;
        node = node->next;
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
    s = lexer(s);
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

t_cmd    *after_parse(t_list  *head)
{
    int i = 0;
    t_list  *node;
    t_cmd   *nm;

    node = head;
    // printf("\x1B[32m");
    // printf("PART--1:\n");
	// printf("\x1B[0m");
    // while(node)
    // {
    //     printf("=> node %d;\n", i);
    //     if (node->cmd)
    //         printf("   command : '%s'\n", node->cmd);
    //     printf("\n\n");
    //     i++;
    //     node = node->next;
    // }
    // printf("\x1B[32m");
    // printf("PART--2:\n");
	// printf("\x1B[0m");
    // after_parse2((nm = parser2(head)));
    nm = parser2(head);
    return (nm);
    // parser2(head);
}

void    after_parse2(t_cmd  *cmd)
{
    int i = 0;
    int i2 = 0;
    t_cmd  *node;

    node = cmd;
    while(node)
    {
        printf("\n");
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

char *lexer(char *s)
{
    int     i;
    int     l;
    int     l2;
    int     start;
    int     sz;
    t_lexer *l_node;
    t_lexer *n;
    char    *new_str;

    i = 0;
    start = 0;
    l = 0;
    l2 = 0;
    sz = ft_strlen(s);
    l_node = NULL;
    new_str = calloc(sz + 1, 1);
    while (i < sz && s[i])
    {
        if(s[i] == ' ')
            i++;
        if (s[i] == '"')
        {
            if (!start)
                start = i + 1;
            i++;
            while (s[i] != '"' && s[i])
            {
                i++;
                l2++;
            }
            add_lexer(&l_node, ft_substr(s, start, l2));
            start = 0;
            l2 = 0;
            i++;
        }   
        if (ft_isalnum(s[i]))
        {
            if (!start)
                start = i;
            while (ft_isalnum(s[i]) && s[i])
            {
                i++;
                l2++;
            }
            add_lexer(&l_node, ft_substr(s, start, l2));
            start = 0;
            l2 = 0;
        }
        else if (s[i] == '|')
        {
            add_lexer(&l_node, ft_substr(s, i, 1));
            i += 1;
            start = 0;
            l2 = 0;
        }
        else if (s[i] == '>' && s[i + 1] != '>')
        {
            add_lexer(&l_node, ft_substr(s, i, 1));
            i += 1;
            start = 0;
            l2 = 0;
        }
        else if (s[i] == '<' && s[i + 1] != '<')
        {
            add_lexer(&l_node, ft_substr(s, i, 1));
            i += 1;
            start = 0;
            l2 = 0;
        }
        else if (s[i] == '>' && s[i + 1] == '>')
        {
            add_lexer(&l_node, ft_substr(s, i, 2));
            i += 2;
            start = 0;
            l2 = 0;
        }
        else if (s[i] == '<' && s[i + 1] == '<')
        {
            add_lexer(&l_node, ft_substr(s, i, 2));
            i += 2;
            start = 0;
            l2 = 0;
        }
        else
            i++;
    }
    n = l_node;
    while (n)
    {
        // printf("\n:%s:\n", n->cmd);
        new_str = ft_strjoin(ft_strjoin(ft_strdup(new_str), ft_strdup(" ")), ft_strdup(n->cmd));
        n = n->next;       
    }
    new_str = ft_strtrim(new_str, " ");
    // printf("\nbefore lexer : '%s'\n", s);
    // printf("after  lexer : '%s'\n\n", new_str);
    return (new_str);
}
