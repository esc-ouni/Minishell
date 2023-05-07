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

t_lexer  *parser()
{
    char    *s;
	t_list	*head;
	t_lexer	*h_lexer;

	head = NULL;
    s = readline(" ");
    h_lexer = lexer(s);
    while (h_lexer)
    {
        printf("'%s'\n", h_lexer->cmd);
        h_lexer = h_lexer->next;
    }
	return (h_lexer);
}

t_cmd  *parser2(t_lexer *head)
{
    char    **full_cmd;
    t_file  *out_files;
    t_file  *in_files;
    t_file  *file;
    t_file  *file2;
    t_lexer  *node;
    t_lexer  *n;
    t_cmd   *cmd;
    t_cmd   *n_cmd;
    int i = 0;
    int i2 = 0;

    node = head;
    full_cmd = NULL;
    cmd = NULL;
    out_files = NULL;
    in_files = NULL;
    while (node)
    {
        if (!strncmp(node->cmd, "|", ft_strlen(node->cmd)))
            node = node->next;
        else
        {
            // CHECK_FOR_OUT_FILES
            n = node;
            while (n && strncmp(n->cmd, "|", ft_strlen(n->cmd)))
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

            // CHECK_FOR_IN_FILES
            n = node;
            while (n && strncmp(n->cmd, "|", ft_strlen(n->cmd)))
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

            // GET_FULL_CMD
            /* add_to_full_cmd*/
            n = node;
            i = 0;
            add_to_cmd(&cmd, full_cmd, out_files, in_files);
            i2++;
            while (full_cmd[i])
            {
                free(full_cmd[i]);
                i++;
            }
            free(full_cmd[i]);
            free(full_cmd);
            i = 0;
            file = out_files;
            while (file)
            {
                file2 = file;
                file = file->next;
                free(file2);
            }
            file = in_files;
            while (file)
            {
                file2 = file;
                file = file->next;
                free(file2);
            }
            full_cmd = NULL;
            out_files = NULL;
            in_files = NULL;
            node = node->next;
        }
    }
    i = 0;

    //UPDATE_CMD
    n_cmd = cmd;
    while (n_cmd)
    {
        if (i == 0)
        {
            n_cmd->first_cmd = 1;
            n_cmd->last_cmd = 0;
        }
        i++;
        n_cmd = n_cmd->next;
    }
    n_cmd = cmd;
    if (ft_cmdsize(n_cmd) == 1)
    {
        n_cmd->first_cmd = 1;
        n_cmd->last_cmd = 1;
    }
    else
    {
        while (n_cmd->next)
            n_cmd = n_cmd->next;
        n_cmd->first_cmd = 0;
        n_cmd->last_cmd = 1;
    }
    return (cmd);
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
            printf("'%s' ", node->cmd[i2]);
            i2++;
        }
        i2 = 0;
        printf("\n");
        printf("   position    : ");
        printf("f:%d ", node->first_cmd);
        printf("l:%d ", node->last_cmd);
        printf("\n");
        printf("   out_files   : ");
        while(node->out_files)
        {
            printf("'%s'->", node->out_files->filename);
            printf("%d ", node->out_files->islast);
            node->out_files = node->out_files->next;
        }
        printf("\n");
        printf("   in_files    : ");
        while(node->in_files)
        {
            printf("'%s'->", node->in_files->filename);
            printf("%d ", node->in_files->islast);
            node->in_files = node->in_files->next;
        }
        printf("\n");
        printf("   cmd_type    : ");
        printf("%d ", node->builtflag); 
        printf("\n\n");
        i++;
        node = node->next;
    }
}

t_lexer *lexer(char *s)
{
    int     i;
    int     l;
    int     l2;
    int     start;
    int     sz;
    t_lexer *l_node;
    t_lexer *n;

    i = 0;
    start = 0;
    l = 0;
    l2 = 0;
    sz = ft_strlen(s);
    l_node = NULL;
    while (i < sz && s[i])
    {
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
        if (ft_isascii(s[i]) && s[i] && s[i] != '>' && s[i] != '<' && s[i] != '|' && s[i] != ' ' && s[i] != '-')
        {
            if (!start)
                start = i;
            while (ft_isascii(s[i]) && s[i] && s[i] != '>' && s[i] != '<' && s[i] != '|' && s[i] != '"' && s[i] != ' ' && s[i] != '-')
            {
                i++;
                l2++;
            }
            add_lexer(&l_node, ft_substr(s, start, l2));
            start = 0;
            l2 = 0;
        }
        else if (s[i] == '-' && s[i] && s[i] != '>' && s[i] != '<' && s[i] != '|' && s[i] != ' ')
        {
            if (!start)
                start = i;
            while (ft_isascii(s[i]) && s[i] && s[i] != '>' && s[i] != '<' && s[i] != '|' && s[i] != '"' && s[i] != ' ')
            {
                i++;
                l2++;
            }
            add_lexer(&l_node, ft_substr(s, start, l2));
            start = 0;
            l2 = 0;
        }
        else if (s[i] == ' ')
            i++;
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
    }
    n = l_node;
    while (n)
    {
        printf(":%s:\n", n->cmd);
        n = n->next;       
    }
    exit(0);
    return (l_node);
}
