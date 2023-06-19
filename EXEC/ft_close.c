/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 11:46:18 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/19 18:56:46 by idouni           ###   ########.fr       */
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
