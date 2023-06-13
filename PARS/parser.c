/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:46:45 by idouni            #+#    #+#             */
/*   Updated: 2023/06/13 16:17:35 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*parser(t_struct *cable, char *s)
{
	t_lexer	*h_lexer;
	t_lexer	*tmp;

	if (check_syntax(cable, s) == 1)
		return (set_exitval(cable, 258), free(s), \
		ft_collectorclear(cable->collector, TMP), NULL);
	else if (check_syntax(cable, s) == 2)
		return (free(s), ft_collectorclear(cable->collector, TMP), NULL);
	h_lexer = lexer(cable, s);
	expander(cable, &h_lexer);
	tmp = h_lexer;
	if (check_syntax2(&h_lexer))
		return (set_exitval(cable, 258), \
		ft_collectorclear(cable->collector, TMP), NULL);
	return (h_lexer);
}

t_cmd	*parser2(t_struct *cable, t_lexer *node)
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
	files = h_malloc(cable->collector, sizeof(t_files), files, TMP);
	parser_init(&out_files, &in_files, &full_cmd);
	while (node)
	{
		check_for_out_files(cable, &out_files, node);
		check_for_in_files(cable, &in_files, node);
		get_full_cmd(cable, &node, &full_cmd);
		if (node && node->type == PIP)
			node = node->next;
		files->out_files = out_files;
		files->in_files = in_files;
		add_to_cmd(cable, &cmd, full_cmd, files);
		parser_init(&out_files, &in_files, &full_cmd);
	}
	return (cmd);
}

void	get_full_cmd(t_struct *cable, t_lexer **n, char ***full_cmd)
{
	int	j;

	j = 1;
	while ((*n) && (*n)->type != PIP)
	{
		if ((*n)->type == WH_SP)
			j = 0;
		else if ((*n)->type == SCMD || (*n)->type == ST_SQ \
		|| (*n)->type == ST_DQ)
		{
			add_to_fullcmd(cable, full_cmd, (*n), j);
			j = 1;
		}
		(*n) = (*n)->next;
	}
}

void	set_exitval(t_struct *cable, int extval)
{
	if (extval)
		cable->exit_val = extval;
}

void	get_sig_exitval(t_struct *cable, int extval)
{
	if (extval == 130 || extval == 131)
		cable->exit_val = extval;
	g_var = 1;
}
