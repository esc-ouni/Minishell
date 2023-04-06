/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:39:57 by msamhaou          #+#    #+#             */
/*   Updated: 2023/04/05 14:42:38 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_get_rawpath(char **env)
{
	int	i;
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
	
	i = 0;
	rawpath = ft_get_rawpath(env);
	paths = ft_split(rawpath, ':');
	free(rawpath);
	while (paths[i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], arg);
		i++;
	}
	return (paths);
}

static char	*ft_get_path(char *arg, char **env)
{
	char	**rawjoin;
	int		i;

	rawjoin = ft_split_raw(arg, env);
	i = 0;
	while (rawjoin[i])
	{
		if (!access(rawjoin[i], X_OK))
			return(rawjoin[i]);
		i++;
	}
	return (NULL);
}

int	ft_execute(char *arg, char **env)
{
	char *path;
	char **cmd;

	cmd = ft_split(arg, ' ');
	path = ft_get_path(cmd[0], env);
	execve(path, cmd, env);
	return (0);
}