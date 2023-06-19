/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_7.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:47:39 by idouni            #+#    #+#             */
/*   Updated: 2023/06/19 18:40:26 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_lexer(t_struct *cable, t_lexer **head, \
char *content, t_enum	type)
{
	t_lexer	*tmp;
	t_lexer	*new_node;

	new_node = NULL;
	new_node = h_malloc(cable->collector, sizeof(t_lexer), new_node, TMP);
	new_node->cmd = ft_mstrdup(cable, content, TMP);
	new_node->type = type;
	if (!(*head))
	{
		*head = new_node;
		new_node->next = NULL;
	}
	else
	{
		tmp = *head;
		while (tmp->next)
		{
			tmp = tmp->next;
		}
		tmp->next = new_node;
		new_node->next = NULL;
	}
}

char	*minimizer(t_struct *cable, char *s)
{
	char	*ns;
	int		i;

	i = 0;
	ns = NULL;
	ns = h_malloc(cable->collector, ft_strlen(s) + 1, ns, TMP);
	while (s[i])
	{
		if (s[i] <= 'Z' && s[i] >= 'A')
			ns[i] = s[i] + 32;
		else
			ns[i] = s[i];
		i++;
	}
	ns[i] = '\0';
	return (ns);
}

t_built	cmd_type(t_struct *cable, char *cmd)
{
	if (!ft_strncmp(minimizer(cable, cmd), "echo", \
	ft_strlen("echo")) && (ft_strlen(cmd) == ft_strlen("echo")))
		return (ECH);
	else if (!ft_strncmp(cmd, "cd", ft_strlen("cd")) && \
	(ft_strlen(cmd) == ft_strlen("cd")))
		return (CD);
	else if (!ft_strncmp(minimizer(cable, cmd), "pwd", \
	ft_strlen("pwd")) && (ft_strlen(cmd) == ft_strlen("pwd")))
		return (PWD);
	else if (!ft_strncmp(cmd, "export", ft_strlen("export")) && \
	(ft_strlen(cmd) == ft_strlen("export")))
		return (EXPT);
	else if (!ft_strncmp(cmd, "unset", ft_strlen("unset")) && \
	(ft_strlen(cmd) == ft_strlen("unset")))
		return (UNST);
	else if (!ft_strncmp(minimizer(cable, cmd), "env", ft_strlen("env")) && \
	(ft_strlen(cmd) == ft_strlen("env")))
		return (ENV);
	else if (!ft_strncmp(cmd, "exit", ft_strlen("exit")) && \
	(ft_strlen(cmd) == ft_strlen("exit")))
		return (EXT);
	else
		return (NOT);
}

int	searcher_for_spc(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '*' && s[i] != '+' && s[i] != '-' && \
	s[i] != '>' && s[i] != '<' && s[i] != '\\' && s[i] != '|' \
	&& s[i] != '#' && s[i] != ' ' && s[i] != '\t' && s[i] != '\'' \
	&& s[i] != '\"' && s[i] != '.' && s[i] != '/')
		i++;
	return (i);
}

void	check_for_in_files(t_struct *cable, t_file **in_files, t_lexer *n)
{
	while (n && n->cmd && n->type != PIP)
	{
		if (n && n->cmd && n->type == R_IN && n->next)
			check_for_rin(cable, in_files, &n);
		else if (n->cmd && n->type == R_HD && n->next)
			check_for_hd(cable, in_files, &n);
		else if (n)
			n = n->next;
		else
			break ;
	}
}
