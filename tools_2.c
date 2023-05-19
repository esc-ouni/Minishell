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

// # include "minishell_pars.h"
#include "Minishell.h"

int	check_syntax2(t_lexer	**h_lexer)
{
	t_lexer *node;

	node = *h_lexer;
	while (node)
	{
		if ((node->type == R_OA) || (node->type == R_OT) || (node->type == R_IN) || (node->type == R_HD))
		{
			if ((node->next) && ((node->next->type == R_OA) || (node->next->type == R_OT) || (node->next->type == R_IN) || (node->next->type == R_HD)))
			{
				printf("syntax error near unexpected token\n");
				return (1);	
			}
			else if (!node->next)
			{
				printf("syntax error near unexpected token\n");
				return (1);		
			}
		}
		node = node->next;
	}
	return (0);
}

void printTYPE(t_enum num) 
{
    switch (num) 
	{
        case WH_SP:
		{
            printf("WH_SP\n");
            break;
		}
        case PIP:
		{
            printf("Pipe\n");
            break;
		}
        case SCMD:
		{
            printf("SCMD\n");
            break;
		}
        // case OPTN:
		// {
        //     printf("OPTN\n");
        //     break;
		// }
        // case ARGS:
		// {
        //     printf("ARGS\n");
        //     break;
		// }
        // case ST_SQ:
		{
            printf("ST_SQ\n");
            break;
		}
        case ST_DQ:
		{
            printf("ST_DQ\n");
            break;
		}
        case R_OA:
		{
            printf("R_OA\n");
            break;
		}
        case R_OT:
		{
            printf("R_OT\n");
            break;
		}
        case R_IN:
		{
            printf("R_IN\n");
            break;
		}
        case R_HD:
		{
            printf("R_HD\n");
            break;
		}
        case FIL_NM:
		{
            printf("FIL_NM\n");
            break;
		}
        default:
            printf("Unknown Type\n");
    }
}

t_lexer  *parser(t_collector	**collector, t_env **env)
{
    char    *s;
	t_lexer	*h_lexer;
	t_lexer	*h2_lexer;

    s = readline("\x1B[34m" "BAASH>> " "\x1B[0m");
	if (check_syntax(s))
		return (NULL);
    h_lexer = lexer(collector, s);
    h2_lexer = h_lexer;
	// while (h2_lexer)
	// {
	// 	printf("\n'%s' type ", h2_lexer->cmd);
	// 	printTYPE(h2_lexer->type);
	// 	h2_lexer = h2_lexer->next;
	// }
	// printf("\n");
	// return (NULL);
	expander(collector, env, &h_lexer);
	// if (check_syntax2(&h_lexer))
	// 	return (NULL);
	return (h_lexer);
}

t_cmd  *parser2(t_collector	**collector, t_lexer *head)
{
    char    **full_cmd;
    t_file  *out_files;
    t_file  *in_files;
    t_lexer  *node;
    t_lexer  *h_lexer;
    t_lexer  *h2_lexer;
    t_lexer  *n;
    t_cmd   *cmd;
    t_cmd   *n_cmd;
    int i = 0;
    int i2 = 0;

    if (!head)
        return (NULL);
    node = head;
    h_lexer = head;
	h2_lexer = h_lexer;
    full_cmd = NULL;
    cmd = NULL;
    out_files = NULL;
    in_files = NULL;
    while (node)
    {
        // CHECK_FOR_OUT_FILES
        n = node;
        while (n && n->type != PIP)
        {
			if (n->cmd && !strcmp(n->cmd, ">") && n->next)
			{
				n = n->next;
				while (n->type == WH_SP)
					n = n->next;
				n->type = FIL_NM;
				add_file_node(collector, &out_files, n->cmd, O_TRUNC);
			}
			if (n->cmd && !strcmp(n->cmd, ">>") && n->next)
			{
				n = n->next;
				while (n && n->type == WH_SP)
					n = n->next;
				n->type = FIL_NM;
				add_file_node(collector, &out_files, n->cmd, O_APPEND);
			}
			n = n->next;
        }

        // CHECK_FOR_IN_FILES
        n = node;
        while (n && n->type != PIP)
        {
			if (n->cmd && !strcmp(n->cmd, "<") && n->next)
			{
				n = n->next;
				while (n && n->type == WH_SP)
					n = n->next;
				n->type = FIL_NM;
				add_file_node(collector, &in_files, n->cmd, O_TRUNC);
			}
			if (n->cmd && !strcmp(n->cmd, "<<") && n->next)
			{
				n = n->next;
				while (n && n->type == WH_SP)
					n = n->next;
				n->type = FIL_NM;
				add_file_node(collector, &in_files, n->cmd, O_APPEND);
			}
			n = n->next;
        }

        // GET_FULL_CMD
        n = node;
		while (n && n->type != PIP)
        {
            if (n->type == R_IN || n->type == R_HD || n->type == R_OT || n->type == R_OA)
            {
                if (n->next)
                {
                    if (n->next->next)
                        n = n->next->next;
                    else
                    {
                        n = NULL;
                        break ;
                    }
                }
            }
            else
            {
				if (n->type != WH_SP && n->type != PIP && n && n->type != R_IN && n->type != R_HD && n->type != R_OT && n->type != R_OA && n->type != FIL_NM)
				{
                	add_to_fullcmd(collector, &full_cmd, n, 1);
					n = n->next;
				}
				else if (n->type != PIP && n && n->type != R_IN && n->type != R_HD && n->type != R_OT && n->type != R_OA)
				{
					while (n && (n->type == WH_SP || n->type == FIL_NM))
						n = n->next;
					if (n && n->type != WH_SP && n->type != PIP && n && n->type != R_IN && n->type != R_HD && n->type != R_OT && n->type != R_OA) 
					{
						add_to_fullcmd(collector, &full_cmd, n, 0);
						n = n->next;
					}
				}
            }
        }
        if (n)
        {
            if (n->type == PIP)
            {
                add_to_cmd(collector, &cmd, full_cmd, out_files, in_files);
                full_cmd = NULL;
                out_files = NULL;
                in_files = NULL;
                i2++;
                n = n->next;   
            }
        }
        else
        {
            add_to_cmd(collector, &cmd, full_cmd, out_files, in_files);
            full_cmd = NULL;
            out_files = NULL;
            in_files = NULL;
            i2++;
            node = n;
        }
        node = n;
    }
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
	// while (h2_lexer)
	// {
	// 	printf("\n'%s' type ", h2_lexer->cmd);
	// 	printTYPE(h2_lexer->type);
	// 	h2_lexer = h2_lexer->next;
	// }
	// printf("\n");
    return (cmd);
}

void    after_parse2(t_cmd  *cmd)
{
    int i = 0;
    int i2 = 0;
    t_cmd  *node;

    node = cmd;
    if (!cmd)
        return ;
    while(node)
    {
        printf("\n");
        printf("=> t_cmd %d;\n", i);
        printf("   command     : ");
        // i2 = 0;
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

t_lexer *lexer(t_collector **collector, char *s)
{
    int     i;
    int     l2;
    int     start;
    int     sz;
    t_lexer *l_node;

    i = 0;
    start = 0;
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
            add_lexer(collector, &l_node, ft_msubstr(collector, s, start, l2), ST_DQ);
            start = 0;
            l2 = 0;
            i++;
        }
        else if (s[i] == '\'')
        {
            if (!start)
                start = i + 1;
            i++;
            while (s[i] != '\'' && s[i])
            {
                i++;
                l2++;
            }
            add_lexer(collector, &l_node, ft_msubstr(collector, s, start, l2), ST_SQ);
            start = 0;
            l2 = 0;
            i++;
        }
        else if (ft_isascii(s[i]) && s[i] && s[i] != '>' && s[i] != '<' && s[i] != '|' && s[i] != '\'' && s[i] != '"' && s[i] != ' ')
        {
            if (!start)
                start = i;
            while (ft_isascii(s[i]) && s[i] && s[i] != '>' && s[i] != '<' && s[i] != '|' && s[i] != '\'' && s[i] != '"' && s[i] != ' ')
            {
                i++;
                l2++;
            }
            add_lexer(collector, &l_node, ft_msubstr(collector, s, start, l2), SCMD);
            start = 0;
            l2 = 0;
        }
        else if (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		{
			add_lexer(collector, &l_node, ft_msubstr(collector, s, i, 1), WH_SP);
            i += 1;
            start = 0;
            l2 = 0;
		}
        else if (s[i] == '|')
        {
            add_lexer(collector, &l_node, ft_msubstr(collector, s, i, 1), PIP);
            i += 1;
            start = 0;
            l2 = 0;
        }
        else if (s[i] == '>' && s[i + 1] != '>')
        {
            add_lexer(collector, &l_node, ft_msubstr(collector, s, i, 1), R_OT);
            i += 1;
            start = 0;
            l2 = 0;
        }
        else if (s[i] == '<' && s[i + 1] != '<')
        {
            add_lexer(collector, &l_node, ft_msubstr(collector, s, i, 1), R_IN);
            i += 1;
            start = 0;
            l2 = 0;
        }
        else if (s[i] == '>' && s[i + 1] == '>')
        {
            add_lexer(collector, &l_node, ft_msubstr(collector, s, i, 2), R_OA);
            i += 2;
            start = 0;
            l2 = 0;
        }
        else if (s[i] == '<' && s[i + 1] == '<')
        {
            add_lexer(collector, &l_node, ft_msubstr(collector, s, i, 2), R_HD);
            i += 2;
            start = 0;
            l2 = 0;
        }
    }
	free(s);
    return (l_node);
}
