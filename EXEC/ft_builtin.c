/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:11:25 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/06 15:11:02 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_cmd *cmd)
{
	char	*path;

	if (!cmd->cmd[1])
		path = getenv("HOME");
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
