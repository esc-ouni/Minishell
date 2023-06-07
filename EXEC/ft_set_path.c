/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 16:25:07 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/07 14:19:22 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_get_rawpath(char **env)
{
	int		i;
	char	*nedl;
	char	*rawpath;

	i = 0;
	nedl = "PATH=";
	while (env[i])
	{
		rawpath = ft_strnstr(env[i++], nedl, ft_strlen(nedl));
		if (rawpath)
		{
			rawpath = ft_substr(rawpath, ft_strlen(nedl), ft_strlen(rawpath));
			return (rawpath);
		}
	}
	return (NULL);
}

static char	**ft_split_raw(char *arg, char **env)
{
	char	**paths;
	char	*rawpath;
	char	*tmp;
	int		i;

	if (!arg || !env)
		return (NULL);
	i = 0;
	rawpath = ft_get_rawpath(env);
	if (!rawpath)
		return (NULL);
	paths = ft_split(rawpath, ':');
	if (!paths)
		return (NULL);
	free(rawpath);
	while (paths[i])
	{
		paths[i] = ft_strjoin(paths[i], "/");
		paths[i] = ft_strjoin(paths[i], arg);
		i++;
	}
	return (paths);
}

static char	*ft_get_path(char **cmd, char **env, t_struct *cable)
{
	char	**rawjoin;
	char	*res;
	int		i;

	if (!cmd || !env)
		return (NULL);
	rawjoin = ft_split_raw(cmd[0], env);
	if (!rawjoin)
		return (NULL);
	i = 0;
	while (rawjoin[i])
	{
		if (!access(rawjoin[i], X_OK))
		{
			res = ft_mstrdup(cable, rawjoin[i], TMP);
			return (ft_free_stringp(rawjoin), res);
		}
		i++;
	}
	ft_free_stringp(rawjoin);
	return (NULL);
}

int	ft_set_path(t_cmd *cmd, t_struct *cable)
{
	while (cmd)
	{
		if (cmd->cmd[0])
		{
			if (!ft_strchr(cmd->cmd[0], '/'))
				cmd->cmd_path = ft_get_path(cmd->cmd, cable->env, cable);
			else
				cmd->cmd_path = cmd->cmd[0];
		}
		cmd = cmd->next;
	}
	return (1);
}
