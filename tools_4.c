/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:23:31 by idouni            #+#    #+#             */
/*   Updated: 2023/06/06 15:22:41 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_mstrdup(t_struct *cable, const char *s1, t_flag flag)
{
	size_t	i;
	char	*s;

	i = 0;
	s = NULL;
	if (!s1)
		return (NULL);
	s = (char *)h_malloc(cable->collector, sizeof(char) * \
	(ft_strlen(s1) + 1), s, flag);
	while (s1[i] != '\0')
	{
		s[i] = s1[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*ft_mstrjoin(t_struct *cable, char const *s1, \
char const *s2, t_flag flag)
{
	size_t		l1;
	size_t		l2;
	char		*ns;

	ns = NULL;
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	ns = (char *)h_malloc(cable->collector, sizeof(char) * \
	(l1 + l2 + 1), ns, flag);
	if (ns)
	{
		if (s1)
			ft_memmove(ns, s1, l1);
		if (s2)
			ft_memmove(ns + l1, s2, l2);
		ns[l2 + l1] = '\0';
		return (ns);
	}
	return (ns);
}

// void	update_cmd(t_cmd *cmd)
// {
// 	int		i;
// 	t_cmd	*n_cmd;

// 	i = 0;
// 	n_cmd = cmd;
// 	if (n_cmd && ft_cmdsize(n_cmd) == 1)
// 	{
// 		n_cmd->first_cmd = 1;
// 		n_cmd->last_cmd = 1;
// 	}
// 	else if (n_cmd && ft_cmdsize(n_cmd) != 1)
// 	{
// 		n_cmd->first_cmd = 0;
// 		n_cmd->last_cmd = 0;
// 		if (i == 0)
// 			n_cmd->first_cmd = 1;
// 		i++;
// 		while (n_cmd->next)
// 			n_cmd = n_cmd->next;
// 		n_cmd->last_cmd = 1;
// 		n_cmd->first_cmd = 0;
// 	}
// }

void	parser_init(t_file **out_files, t_file **in_files, char ***full_cmd)
{
	*full_cmd = NULL;
	*out_files = NULL;
	*in_files = NULL;
}

void	expnd_v(t_struct *cable, t_lexer *node, char **str)
{
	if (ft_strlen (node->cmd) == 1 && node->cmd[0] == '$' && \
	((node->next && node->next->type != ST_SQ && \
	node->next->type != ST_DQ) || !node->next))
		(*str) = ft_mstrjoin(cable, (*str), node->cmd, TMP);
	else if ((ft_strlen(node->cmd) == 1 && node->cmd[0] == '$'))
		(*str) = ft_mstrjoin(cable, (*str), NULL, TMP);
	else
		expnd_2(cable, node, str);
}
