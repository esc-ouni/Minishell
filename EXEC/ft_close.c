/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 11:46:18 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/14 13:42:57 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close(t_struct *cable, int fd)
{
	if (close(fd) == -1)
	{
		if (errno == EBADF)
			return ;
		else
		{
			perror("close");
			ft_collectorclear(cable->collector, ALL);
		}
	}
}
