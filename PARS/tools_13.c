/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_13.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:09:45 by idouni            #+#    #+#             */
/*   Updated: 2023/06/18 15:35:36 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_for_ot(t_struct *cable, t_file **out_files, t_lexer **n)
{
	char	*filename;

	filename = NULL;
	(*n) = (*n)->next;
	while ((*n) && (*n)->type == WH_SP)
		(*n) = (*n)->next;
	while ((*n) && (*n)->cmd && (*n)->type != WH_SP && (*n)->type != PIP && \
	((*n)->type == SCMD || (*n)->type == ST_SQ || (*n)->type == ST_DQ))
	{
		(*n)->type = FIL_NM;
		filename = ft_mstrjoin(cable, filename, (*n)->cmd, TMP);
		(*n) = (*n)->next;
	}
	add_file_node(cable, out_files, filename, O_TRUNC);
}

void	check_for_oa(t_struct *cable, t_file **out_files, t_lexer **n)
{
	char	*filename;

	filename = NULL;
	(*n) = (*n)->next;
	while ((*n) && (*n)->type == WH_SP)
		(*n) = (*n)->next;
	while ((*n) && (*n)->cmd && (*n)->type != WH_SP && (*n)->type != PIP && \
	((*n)->type == SCMD || (*n)->type == ST_SQ || (*n)->type == ST_DQ))
	{
		(*n)->type = FIL_NM;
		filename = ft_mstrjoin(cable, filename, (*n)->cmd, TMP);
		(*n) = (*n)->next;
	}
	add_file_node(cable, out_files, filename, O_APPEND);
}

void	check_for_out_files(t_struct *cable, t_file **out_files, t_lexer *n)
{
	while (n && n->cmd && n->type != PIP)
	{
		if (n && n->cmd && n->type == R_OT && n->next)
			check_for_ot(cable, out_files, &n);
		else if (n->cmd && n->type == R_OA && n->next)
			check_for_oa(cable, out_files, &n);
		else if (n)
			n = n->next;
		else
			break ;
	}
}

void	check_for_rin(t_struct *cable, t_file **in_files, t_lexer **n)
{
	char	*filename;

	filename = NULL;
	(*n) = (*n)->next;
	while ((*n) && (*n)->type == WH_SP)
		(*n) = (*n)->next;
	while ((*n) && (*n)->cmd && (*n)->type != WH_SP && (*n)->type != PIP && \
	((*n)->type == SCMD || (*n)->type == ST_SQ || (*n)->type == ST_DQ))
	{
		(*n)->type = FIL_NM;
		filename = ft_mstrjoin(cable, filename, (*n)->cmd, TMP);
		(*n) = (*n)->next;
	}
	add_file_node(cable, in_files, filename, O_TRUNC);
}

void	check_for_hd(t_struct *cable, t_file **in_files, t_lexer **n)
{
	char	*filename;

	filename = NULL;
	(*n) = (*n)->next;
	while ((*n) && (*n)->type == WH_SP)
		(*n) = (*n)->next;
	while ((*n) && (*n)->cmd && (*n)->type != WH_SP && (*n)->type != PIP && \
	((*n)->type == SCMD || (*n)->type == ST_SQ || (*n)->type == ST_DQ))
	{
		if ((*n)->type == SCMD)
			cable->rd = 1;
		else if ((*n)->type == ST_SQ || (*n)->type == ST_DQ)
			cable->rd = 666;
		(*n)->type = FIL_NM;
		filename = ft_mstrjoin(cable, filename, (*n)->cmd, TMP);
		(*n) = (*n)->next;
	}
	add_file_node(cable, in_files, filename, O_APPEND);
}
