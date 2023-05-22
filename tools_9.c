/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_9.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:44:23 by idouni            #+#    #+#             */
/*   Updated: 2023/05/22 15:20:11 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void	whsp_lex(t_collector **collector, t_lexer **l_node, char *s, int *i)
{
	add_lexer(collector, l_node, ft_msubstr(collector, s, (*i), 1), WH_SP);
	(*i) += 1;
}

void	pip_lex(t_collector **collector, t_lexer **l_node, char *s, int *i)
{
	add_lexer(collector, l_node, ft_msubstr(collector, s, *i, 1), PIP);
	(*i) += 1;
}

void	rot_lex(t_collector **collector, t_lexer **l_node, char *s, int *i)
{
	add_lexer(collector, l_node, ft_msubstr(collector, s, (*i), 1), R_OT);
	(*i) += 1;
}

void	rin_lex(t_collector **collector, t_lexer **l_node, char *s, int *i)
{
	add_lexer(collector, l_node, ft_msubstr(collector, s, (*i), 1), R_IN);
	(*i) += 1;
}

void	roa_lex(t_collector **collector, t_lexer **l_node, char *s, int *i)
{
	add_lexer(collector, l_node, ft_msubstr(collector, s, (*i), 2), R_OA);
	(*i) += 2;
}
