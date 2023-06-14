/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 11:46:18 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/14 13:58:12 by msamhaou         ###   ########.fr       */
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
			ft_close_fdtmp(cable);
			ft_collectorclear(cable->collector, ALL);
		}
	}
}

void	ft_close_fdtmp(t_struct *cable)
{
	ft_close(cable, cable->tmp_err);
	ft_close(cable, cable->tmp_fd_in);
}
