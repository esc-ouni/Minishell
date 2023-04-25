/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:50:41 by msamhaou          #+#    #+#             */
/*   Updated: 2023/04/25 15:37:21 by msamhaou         ###   ########.fr       */
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

	if (lol->cmd[1] && lol->cmd[1][0] != '$')
		printf("%s\n", lol->cmd[1]);
	else if (lol->cmd[1][0] == '$')
	{
		s = ft_substr(lol->cmd[1], 1, ft_strlen(lol->cmd[1]));
		if (getenv(s))
			printf("%s\n", getenv(s));
		else
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

char	**ft_export(char **env, char *str)
{
	int		i;
	int		j;
	char	**res;

	i = 0;
	j = 0;
	while (env[i])
		i++;
	res = (char **)malloc(sizeof(char *) * (i + 2));
	while (j < i)
	{
		res[j] = ft_strdup(env[j]);
		if (!res[j])
			return (ft_free_pos(res, j), NULL);
		j++;
	}
	res[j] = ft_strdup(str);
	res[j + 1] = NULL;
	ft_free_old_env(env);
	return(res);
}
