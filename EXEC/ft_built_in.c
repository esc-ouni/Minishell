/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:50:41 by msamhaou          #+#    #+#             */
/*   Updated: 2023/05/30 21:10:10 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ft_builtin(t_cmd *lol, t_init *init)
{
	if (lol->builtflag == ECH)
		ft_echo(lol);
	else if (lol->builtflag == PWD)
		ft_pwd();
	else if (lol->builtflag == ENV)
		ft_env(init->myenv);
	else if (lol->builtflag == EXPT && !lol->cmd[1])
		ft_printlst(init->exp_lst);
	return (0);
}
