/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_8.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:44:34 by idouni            #+#    #+#             */
/*   Updated: 2023/06/06 20:08:35 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	emplify(t_struct *cable, t_cmd *cmd)
{
	t_cmd	*n_cmd;

	if (!cmd)
		return ;
	n_cmd = cmd;
	while (n_cmd)
	{
		if (n_cmd->cmd[0])
			n_cmd->builtflag = cmd_type(cable, n_cmd->cmd[0]);
		else
			n_cmd->builtflag = NOT;
		update_in_out_files(n_cmd->out_files, n_cmd->in_files);
		n_cmd = n_cmd->next;
	}
	// update_cmd(cmd);
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

char	*ft_getenv(t_struct *cable, char *key)
{
	char		*key_part;
	t_envlst	*env;

	key_part = NULL;
	env = cable->envlst;
	while (env)
	{
		key_part = ft_msplit(cable, env->str, '=', TMP)[0];
		if (!(ft_strncmp(key, key_part, ft_strlen(key))) \
		&& (ft_strlen(key) == ft_strlen(key_part)))
			return (ft_strchr(env->str, '=') + 1);
		key_part = NULL;
		env = env->next;
	}
	return (NULL);
}

int	check_str(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != ' ' || s[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

void	rhd_lex(t_struct *cable, t_lexer **l_node, char *s, int *i)
{
	add_lexer(cable, l_node, ft_msubstr(cable, s, (*i), 2), R_HD);
	(*i) += 2;
}
