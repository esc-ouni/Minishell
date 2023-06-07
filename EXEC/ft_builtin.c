/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:11:25 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/07 20:55:29 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_oldpwd(t_struct *cable)
{
	char	*pwd;
	char	*oldpwd;

	pwd = ft_getcwd();
	oldpwd = ft_mstrjoin(cable, "OLDPWD=", pwd, NTMP);
	free(pwd);
	ft_export(cable, oldpwd);
}

char	*ft_get_oldpwd(t_struct *cable)
{
	t_envlst	*exist;

	exist = ft_var_env_exist(cable->envlst, "OLDPWD=");
	if (exist)
		return (ft_strchr(exist->str, '=') + 1);
	return (NULL);
}

int	ft_cd(t_cmd *cmd, t_struct *cable)
{
	char	*path;

	ft_set_oldpwd(cable);
	if (!cmd->cmd[1])
		path = getenv("HOME");
	else if (!ft_strcmp(cmd->cmd[1], "-"))
	{
		path = ft_get_oldpwd(cable);
		if (!path)
			return (ft_putendl_fd("cd: OLDPWD not set", 2), 1);
	}
	else
		path = cmd->cmd[1];
	if ((chdir(path) < 0))
		perror("");
	return (0);
}

void	ft_quit(t_built flag, t_struct *cable)
{
	if (flag == EXT)
		write(1, "exit\n", 5);
	exit(0);
}

int	ft_echo_option(t_cmd *cmd, int *i)
{
	if (!ft_strncmp(cmd->cmd[*i], "-n", ft_strlen("-n")))
	{
		(*i)++;
		return (1);
	}
	return (0);
}

int	ft_echo(t_cmd *lol)
{
	char	*s;
	int		i;
	int		option;

	i = 1;
	option = ft_echo_option(lol, &i);
	s = NULL;
	if (lol->cmd[i])
	{
		while (lol->cmd[i])
		{
			s = ft_strjoin(s, lol->cmd[i]);
			if (lol->cmd[i + 1])
				s = ft_strjoin(s, " ");
			i++;
		}
		printf("%s", s);
		if (!option)
			printf("\n");
	}
	else
		printf("\n");
	return (0);
}

char	*ft_getcwd(void)
{
	char	*buff;

	buff = malloc(1024 * sizeof(char));
	getcwd(buff, 1024);
	return (buff);
}

int	ft_pwd(void)
{
	char	*pwd;

	pwd = ft_getcwd();
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}

void	ft_env(char **myenv)
{
	int	i;

	i = 0;
	while (myenv[i])
		ft_putendl_fd(myenv[i++], STDOUT_FILENO);
}

int	ft_builtin(t_cmd *lol, t_struct *cable)
{
	if (lol->builtflag == ECH)
		ft_echo(lol);
	else if (lol->builtflag == PWD)
		ft_pwd();
	else if (lol->builtflag == ENV)
		ft_env(cable->env);
	else if (lol->builtflag == EXPT && !lol->cmd[1])
		ft_print_exp(cable->exp);
	return (0);
}
