/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:39:57 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/01 17:41:58 by idouni           ###   ########.fr       */
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

void	sig_hdandle(int sig)
{
	if (sig == SIGINT)
		exit(0);
}

char	*ft_get_path(char **cmd, char **env)
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
			res = ft_strdup(rawjoin[i]);
			return (ft_free_stringp(rawjoin), res);
		}
		i++;
	}
	ft_free_stringp(rawjoin);
	return (NULL);
}
