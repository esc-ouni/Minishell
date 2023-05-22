/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_8.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:44:34 by idouni            #+#    #+#             */
/*   Updated: 2023/05/22 17:36:46 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	emplify(t_collector **collector, t_cmd *cmd, char **env)
{
	t_cmd	*n_cmd;
	char	**menv;

	if (!cmd)
		return ;
	menv = mgetenv(collector, env);
	n_cmd = cmd;
	while (n_cmd)
	{
		n_cmd->num_cmds = ft_cmdsize(cmd);
		// n_cmd->myenv = menv;
		if (n_cmd->cmd[0])
			n_cmd->builtflag = cmd_type(collector, n_cmd->cmd[0]);
		update_in_out_files(n_cmd->out_files, n_cmd->in_files);
		n_cmd = n_cmd->next;
	}
	update_cmd(cmd);
}

void	update_in_out_files(t_file *out_files, t_file *in_files)
{
	t_file	*h_file;

	h_file = out_files;
	if (h_file)
	{
		while (h_file->next)
		{
			h_file->islast = 0;
			h_file = h_file->next;
		}
		h_file->islast = 1;
	}
	h_file = in_files;
	if (h_file)
	{
		while (h_file->next)
		{
			h_file->islast = 0;
			h_file = h_file->next;
		}
		h_file->islast = 1;
	}
}

char	*ft_getenv(t_collector **collector, char *key, t_env **menv)
{
	t_env	*env;
	char	*key_part;

	key_part = NULL;
	env = *menv;
	while (env)
	{
		key_part = ft_msplit(collector, env->str, '=')[0];
		if (!(ft_strncmp(key, key_part, ft_strlen(key))) \
		&& (ft_strlen(key) == ft_strlen(key_part)))
			return (ft_strchr(env->str, '=') + 1);
		key_part = NULL;
		env = env->next;
	}
	return (NULL);
}

void	rhd_lex(t_collector **collector, t_lexer **l_node, char *s, int *i)
{
	add_lexer(collector, l_node, ft_msubstr(collector, s, (*i), 2), R_HD);
	(*i) += 2;
}

int	check_syntax(char *s)
{
	if (!s)
	{
		write(1, "exit\n", 5);
		exit (0);
	}
	if (!ft_strlen(s))
		return (1);
	add_history(s);
	if (check_oerr(s))
		return (1);
	if (check_pipes(s))
		return (1);
	return (0);
}
