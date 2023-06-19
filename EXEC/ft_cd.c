/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:32:10 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/19 22:34:05 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_set_oldpwd(t_struct *cable)
{
	char	*pwd;
	char	*oldpwd;

	pwd = ft_getcwd(cable);
	oldpwd = ft_mstrjoin(cable, "OLDPWD=", pwd, NTMP);
	return (oldpwd);
}

static char	*ft_set_newpwd(t_struct *cable)
{
	char	*pwd;
	char	*newpwd;

	pwd = ft_getcwd(cable);
	if (errno == ENOENT)
		perror("");
	newpwd = ft_mstrjoin(cable, "PWD=", pwd, NTMP);
	ft_export(cable, newpwd);
	return (newpwd);
}

static char	*ft_get_oldpwd(t_struct *cable)
{
	t_envlst	*exist;

	exist = ft_var_env_exist(cable->envlst, "OLDPWD=", cable);
	if (exist)
		return ((ft_strchr(exist->str, '=') + 1));
	return (NULL);
}

int	ft_cd(t_cmd *cmd, t_struct *cable)
{
	char	*path;
	char	*oldpwd;

	if (!cmd->cmd[1])
		path = getenv("HOME");
	else if (!ft_strcmp(cmd->cmd[1], "-"))
	{
		path = ft_get_oldpwd(cable);
		if (!path)
			return (ft_putendl_fd("cd: OLDPWD not set", 2), 1);
		printf("%s\n", path);
	}
	else
		path = cmd->cmd[1];
	oldpwd = ft_set_oldpwd(cable);
	if ((chdir(path) < 0) && errno != ENOENT)
		perror("");
	ft_set_newpwd(cable);
	ft_export(cable, oldpwd);
	return (0);
}
