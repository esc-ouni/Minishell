/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in_plus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 01:17:39 by msamhaou          #+#    #+#             */
/*   Updated: 2023/05/21 01:21:15 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_built_in_first(t_cmd *lol, char ***myenv, t_env **env_lst)
{
	if (lol->num_cmds > 1)
		return (1);
	if (lol->builtflag == CD)
	{
		ft_cd(lol);
		return (0);
	}
	else if (lol->builtflag == EXT)
		ft_quit(NOT);
	else if (lol->builtflag == EXPT)
	{
		*myenv = ft_export(env_lst, lol->cmd[1],*myenv);
		return (0);
	}
	else if (lol->builtflag == UNST)
	{
		*myenv = ft_unset(env_lst, lol->cmd[1], *myenv);
		return (0);
	}
	return (1);
}

void	ft_env(char **myenv)
{
	int	i;

	i = 0;
	while (myenv[i])
		ft_putendl_fd(myenv[i++], STDOUT_FILENO);
}

int	ft_cd(t_cmd *lol)
{
	char	*path;

	if (!lol->cmd[1])
		path = getenv("HOME");
	else
		path = lol->cmd[1];
	if ((chdir(path) < 0))
		perror("");
	return (0);
}
