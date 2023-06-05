/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_9.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:44:23 by idouni            #+#    #+#             */
/*   Updated: 2023/06/05 12:11:36 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	whsp_lex(t_struct *cable, t_lexer **l_node, char *s, int *i)
{
	add_lexer(cable, l_node, ft_msubstr(cable, s, (*i), 1), WH_SP);
	(*i) += 1;
}

void	pip_lex(t_struct *cable, t_lexer **l_node, char *s, int *i)
{
	add_lexer(cable, l_node, ft_msubstr(cable, s, *i, 1), PIP);
	(*i) += 1;
}

void	rot_lex(t_struct *cable, t_lexer **l_node, char *s, int *i)
{
	add_lexer(cable, l_node, ft_msubstr(cable, s, (*i), 1), R_OT);
	(*i) += 1;
}

void	rin_lex(t_struct *cable, t_lexer **l_node, char *s, int *i)
{
	add_lexer(cable, l_node, ft_msubstr(cable, s, (*i), 1), R_IN);
	(*i) += 1;
}

void	roa_lex(t_struct *cable, t_lexer **l_node, char *s, int *i)
{
	add_lexer(cable, l_node, ft_msubstr(cable, s, (*i), 2), R_OA);
	(*i) += 2;
}
