/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_11.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:09:45 by idouni            #+#    #+#             */
/*   Updated: 2023/05/27 12:38:51 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expnd_v(t_collector **collector, t_env **env, t_lexer *node, char **str)
{
	if (ft_strlen (node->cmd) == 1 && node->cmd[0] == '$' && \
	((node->next && node->next->type != ST_SQ && \
	node->next->type != ST_DQ) || !node->next))
		(*str) = ft_mstrjoin(collector, (*str), node->cmd);
	else if ((ft_strlen(node->cmd) == 1 && node->cmd[0] == '$'))
		(*str) = ft_mstrjoin(collector, (*str), NULL);
	else
		expnd_2(collector, env, node, str);
}
