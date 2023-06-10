/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:38:14 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/10 14:08:15 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_n(const char *str)
{
	char	*s;

	s = (char *)str;
	if (*(s++) != '-')
		return (0);
	while (*s)
	{
		if (*(s++) != 'n')
			return (0);
	}
	return (1);
}

static int	ft_echo_option(const char *cmd)
{
	char	*str;

	str = (char *)cmd;
	if (ft_is_n(str))
		return (1);
	return (0);
}

static char	*ft_option_break(t_struct *cable, char **cmd, int *option)
{
	int		i;
	int		op_end;
	char	*s;

	op_end = 0;
	s = NULL;
	i = 1;
	while (cmd[i])
	{
		if (!op_end)
			*option = ft_echo_option(cmd[i]);
		if (!(*option))
		{
			s = ft_mstrjoin(cable, s, cmd[i], TMP);
			if (cmd[i + 1])
				s = ft_mstrjoin(cable, s, " ", TMP);
			op_end = 1;
		}
		i++;
	}
	return (s);
}

int	ft_echo(t_cmd *cmd, t_struct *cable)
{
	char	*s;
	int		option;

	s = NULL;
	option = 0;
	if (!cmd->cmd[1])
		return (ft_putstr_fd("\n", 1), 0);
	s = ft_option_break(cable, cmd->cmd, &option);
	ft_putstr_fd(s, 1);
	if (!option)
		ft_putstr_fd("\n", 1);
	return (0);
}
