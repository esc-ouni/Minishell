/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:50:41 by msamhaou          #+#    #+#             */
/*   Updated: 2023/05/04 17:29:22 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_cmd *lol)
{
	if (chdir(lol->cmd[1]) < 0)
		perror("");
	return (0);
}

char	*ft_getcwd()
{
	char	*buff;

	buff = malloc(1024 * sizeof(char));
	getcwd(buff, 1024);
	return (buff);
}

int	ft_pwd()
{
	char	*pwd;
	
	pwd = ft_getcwd();
	printf("%s\n", pwd);
	free(pwd);
	return(0);
}

int	ft_echo(t_cmd *lol)
{
	char	*s;
	int		i;
	int		option;

	i = 1;
	option = 0;
	s = NULL;
	if (!strncmp(lol->cmd[i], "-n", ft_strlen(lol->cmd[i])))
	{
		option = 1;
		i++;
	}
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

void	ft_free_old_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		free(env[i++]);
	free(env);
}

void	ft_env(char **myenv)
{
	int	i;

	i = 0;
	while (myenv[i])
		ft_putendl_fd(myenv[i++], STDOUT_FILENO);
}