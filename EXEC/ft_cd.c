/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:32:10 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/13 16:36:25 by msamhaou         ###   ########.fr       */
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
	{
		ft_putstr_fd("cd: error retrieving current directory: ", 2);
		ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
		ft_putendl_fd(strerror(errno), 2);
	}
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
	if ((chdir(path) < 0))
		perror("");
	ft_set_newpwd(cable);
	ft_export(cable, oldpwd);
	return (0);
}
