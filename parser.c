#include "Minishell.h"

t_lexer  *parser(t_collector	**collector, t_env **env)
{
    char    *s;
	t_lexer	*h_lexer;

    s = readline("\x1B[34m" "BAASH>> " "\x1B[0m");
	if (check_syntax(s))
		return (NULL);
    h_lexer = lexer(collector, s);
	expander(collector, env, &h_lexer);
	if (check_syntax2(&h_lexer))
		return (NULL);
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
    return (cmd);
}
