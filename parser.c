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

void	parser_init(t_file **out_files, t_file **in_files, char ***full_cmd)
{
	*full_cmd = NULL;
    *out_files = NULL;
    *in_files = NULL;
}


t_cmd  *parser2(t_collector	**collector, t_lexer *node)
{
	t_files		*files;
    char		**full_cmd;
    t_file		*out_files;
    t_file		*in_files;
    t_cmd		*cmd;
    
    if (!node)
        return (NULL);
    cmd = NULL;
	files = NULL;
	files = h_malloc(collector, sizeof(t_files), files);
	files->out_files = NULL;
	files->in_files = NULL;
	parser_init(&out_files, &in_files, &full_cmd);
    while (node)
    {
		check_for_out_files(collector, &out_files, node);
		check_for_in_files(collector, &in_files, node);
		get_full_cmd(collector, &node, &full_cmd);
		if (node && node->type == PIP)
			node = node->next;
		files->out_files = out_files;
		files->in_files = in_files;
        // add_to_cmd(collector, &cmd, full_cmd, out_files, in_files);
        add_to_cmd(collector, &cmd, full_cmd, files);
		parser_init(&out_files, &in_files, &full_cmd);
    }
	update_cmd(cmd);
    return (cmd);
}

void	get_full_cmd(t_collector **collector, t_lexer **n, char ***full_cmd)
{
	int j;

	j = 1;
	while ((*n) && (*n)->type != PIP)
	{
		if ((*n)->type == WH_SP)
			j = 0;
		else if ((*n)->type == SCMD || (*n)->type == ST_SQ || (*n)->type == ST_DQ)
		{
			add_to_fullcmd(collector, full_cmd, (*n), j);
			j = 1;
		}
		(*n) = (*n)->next;
	}
}

void	check_for_in_files(t_collector **collector, t_file **in_files, t_lexer *n)
{
	while (n && n->type != PIP)
	{
		if (n->cmd && !strcmp(n->cmd, "<") && n->next)
		{
			n = n->next;
			while (n && n->type == WH_SP)
				n = n->next;
			n->type = FIL_NM;
			add_file_node(collector, in_files, n->cmd, O_TRUNC);
		}
		if (n->cmd && !strcmp(n->cmd, "<<") && n->next)
		{
			n = n->next;
			while (n && n->type == WH_SP)
				n = n->next;
			n->type = FIL_NM;
			add_file_node(collector, in_files, n->cmd, O_APPEND);
		}
		n = n->next;
	}
}

void	check_for_out_files(t_collector **collector, t_file **out_files, t_lexer *n)
{
	while (n && n->type != PIP)
	{
		if (n->cmd && !strcmp(n->cmd, ">") && n->next)
		{
			n = n->next;
			while (n->type == WH_SP)
				n = n->next;
			n->type = FIL_NM;
			add_file_node(collector, out_files, n->cmd, O_TRUNC);
		}
		if (n->cmd && !strcmp(n->cmd, ">>") && n->next)
		{
			n = n->next;
			while (n && n->type == WH_SP)
				n = n->next;
			n->type = FIL_NM;
			add_file_node(collector, out_files, n->cmd, O_APPEND);
		}
		n = n->next;
	}
}

void	update_cmd(t_cmd *cmd)
{
	int		i;
    t_cmd   *n_cmd;

	i = 0;
	n_cmd = cmd;
    if (n_cmd && ft_cmdsize(n_cmd) == 1)
    {
        n_cmd->first_cmd = 1;
        n_cmd->last_cmd = 1;
    }
	else if (n_cmd && ft_cmdsize(n_cmd) != 1)
	{
		n_cmd->first_cmd = 0;
    	n_cmd->last_cmd = 0;
		if (i == 0)
            n_cmd->first_cmd = 1;
        i++;
        while (n_cmd->next)
            n_cmd = n_cmd->next;
        n_cmd->last_cmd = 1;
		n_cmd->first_cmd = 0;
	}
}
