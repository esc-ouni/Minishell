/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:38:14 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/10 23:02:12 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_option(const char *str)
{
	char	*s;

	s = (char *)str;
	if (*(s++) != '-')
		return (0);
	while (*s)
		if (*(s++) != 'n')
			return (0);
	return (1);
}

static char	*ft_echo_handle(t_struct *cable, char **arg)
{
	int		i;
	char	*s;
	int		flag;
	int		option;

	s = NULL;
	i = 1;
	flag = 0;
	option = 0;
	while (arg[i])
	{
		if (!flag)
			option = ft_is_option(arg[i]);
		if (!(option))
		{
			s = ft_mstrjoin(cable, s, arg[i], TMP);
			if (arg[i + 1])
				s = ft_mstrjoin(cable, s, " ", TMP);
			flag = 1;
		}
		i++;
	}
	return (s);
}

int	ft_echo(t_cmd *lol, t_struct *cable)
{
	char	*s;
	int		i;
	int		option;

	i = 1;
	s = NULL;
	if (!lol->cmd[1])
		printf("\n");
	option = ft_is_option(lol->cmd[1]);
	s = ft_echo_handle(cable, lol->cmd);
	ft_putstr_fd(s, 1);
	if (!option)
		ft_putstr_fd("\n", 1);
	return (0);
}
