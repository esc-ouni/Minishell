/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 11:46:18 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/14 12:29:45 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close(t_struct *cable, int fd, int i)
{
	if (close(fd) == -1)
	{
		ft_putnbr_fd(i ,2);
		ft_putendl_fd(" ",2);
		ft_putnbr_fd(fd ,2);
		ft_putendl_fd(" ",2);
		// perror("close");
		if (errno == EBADF)
			return ;
		else
		{
			ft_collectorclear(cable->collector, ALL);
		}
	}
}
