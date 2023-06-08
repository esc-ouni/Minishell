/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:11:52 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/08 14:33:29 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_quit(t_built flag)
{
	if (flag == EXT)
		write(1, "exit\n", 5);
	exit(0);
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
