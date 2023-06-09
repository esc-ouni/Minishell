/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:11:52 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/09 17:11:51 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_quit(t_cmd *cmd)
{
	int	ext;

	write(1, "exit\n", 5);
	ext = 0;
	if (cmd->cmd[2])
		return (ft_print_err(NULL, 0));
	else if (!ft_strdigit(cmd->cmd[1]))
		ft_print_err(cmd->cmd[1], 1);
	else
	{
		ext = ft_atoi(cmd->cmd[1]);
		exit(ext);
	}
	exit(ext);
}

char	*ft_getcwd(t_struct *cable)
{
	char	*buff;

	buff = NULL;
	buff = h_malloc(cable->collector, 1024 * sizeof(char), buff, TMP);
	getcwd(buff, 1024);
	return (buff);
}

int	ft_pwd(t_struct *cable)
{
	char	*pwd;

	pwd = ft_getcwd(cable);
	printf("%s\n", pwd);
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
		ft_echo(lol, cable);
	else if (lol->builtflag == PWD)
		ft_pwd(cable);
	else if (lol->builtflag == ENV)
		ft_env(cable->env);
	else if (lol->builtflag == EXPT && !lol->cmd[1])
		ft_print_exp(cable->exp);
	return (0);
}
