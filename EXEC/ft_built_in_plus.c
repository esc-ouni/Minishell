/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in_plus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 01:17:39 by msamhaou          #+#    #+#             */
/*   Updated: 2023/05/30 20:53:16 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exp_loop(t_cmd *lol, t_init *init)
{
	int	i;

	i = 1;
	if (!lol->cmd[i])
		return ;
	while (lol->cmd[i])
		init->myenv = ft_export(init, lol->cmd[i++]);
}

void	ft_unset_loop(t_cmd *lol, t_init *init)
{
	int	i;

	i = 1;
	if (!lol->cmd[i])
		return ;
	while (lol->cmd[i])
		init->myenv = ft_unset(init, lol->cmd[i++]);
}

int	ft_built_in_first(t_cmd *lol, t_init *init)
{
	if (lol->num_cmds > 1)
		return (1);
	if (lol->builtflag == CD)
	{
		ft_cd(lol);
		return (0);
	}
	else if (lol->builtflag == EXT)
		ft_quit(NOT, init);
	else if (lol->builtflag == EXPT && lol->cmd[1])
	{
		ft_exp_loop(lol, init);
		return (0);
	}
	else if (lol->builtflag == UNST)
	{
		ft_unset_loop(lol, init);
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
