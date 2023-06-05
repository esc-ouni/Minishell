/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_7.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:47:39 by idouni            #+#    #+#             */
/*   Updated: 2023/05/23 16:19:34 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_lexer(t_collector **collector, t_lexer **head, \
char *content, t_enum	type)
{
	t_lexer	*tmp;
	t_lexer	*new_node;

	new_node = NULL;
	new_node = h_malloc(collector, sizeof(t_lexer), new_node);
	new_node->cmd = ft_mstrdup(collector, content);
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

char	**mgetenv(t_collector **collector, char **env)
{
	int		i;
	char	**new_env;

	i = 0;
	new_env = NULL;
	while (env[i])
		i++;
	new_env = h_malloc(collector, sizeof(char *) * (i + 1), new_env);
	i = -1;
	while (env[++i])
		new_env[i] = ft_mstrdup(collector, env[i]);
	new_env[i] = NULL;
	return (new_env);
}

char	*minimizer(t_collector **collector, char *s)
{
	char	*ns;
	int		i;

	i = 0;
	ns = NULL;
	ns = h_malloc(collector, ft_strlen(s) + 1, ns);
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

t_built	cmd_type(t_collector **collector, char *cmd)
{
	if (!ft_strncmp(minimizer(collector, cmd), "echo", \
	ft_strlen("echo")) && (ft_strlen(cmd) == ft_strlen("echo")))
		return (ECH);
	else if (!ft_strncmp(cmd, "cd", ft_strlen("cd")) && \
	(ft_strlen(cmd) == ft_strlen("cd")))
		return (CD);
	else if (!ft_strncmp(minimizer(collector, cmd), "pwd", \
	ft_strlen("pwd")) && (ft_strlen(cmd) == ft_strlen("pwd")))
		return (PWD);
	else if (!ft_strncmp(cmd, "export", ft_strlen("export")) && \
	(ft_strlen(cmd) == ft_strlen("export")))
		return (EXPT);
	else if (!ft_strncmp(cmd, "unset", ft_strlen("unset")) && \
	(ft_strlen(cmd) == ft_strlen("unset")))
		return (UNST);
	else if (!ft_strncmp(minimizer(collector, cmd), "env", ft_strlen("env")) && \
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
	&& s[i] != '#' && s[i] != ' ' && s[i] != '\t' && s[i] != '\'')
		i++;
	return (i);
}
