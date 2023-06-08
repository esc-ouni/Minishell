/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:38:14 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/08 11:40:32 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_echo_option(t_cmd *cmd, int *i)
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
