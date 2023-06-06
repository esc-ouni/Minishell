/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_15.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:09:45 by idouni            #+#    #+#             */
/*   Updated: 2023/06/06 16:46:54 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syntax2(t_lexer **h_lexer)
{
	if (basic_syntax_check(h_lexer))
		return (1);
	else if (basic_syntax_check2(h_lexer))
		return (1);
	return (0);
}

void	check_for_in_files(t_struct *cable, t_file **in_files, t_lexer *n)
{
	while (n && n->cmd && n->type != PIP)
	{
		if (n && n->cmd && n->type == R_IN && n->next)
			check_for_rin(cable, in_files, &n);
		else if (n->cmd && n->type == R_HD && n->next)
			check_for_hd(cable, in_files, &n);
		if (n)
			n = n->next;
		else
			break ;
	}
}
