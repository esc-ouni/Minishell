/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_in_out_files.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 21:05:03 by msamhaou          #+#    #+#             */
/*   Updated: 2023/05/31 18:13:53 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_open_out_files(t_cmd *lol)
{
	t_file	*files;

	files = lol->out_files;
	while (files)
	{
		lol->cmd_fdout = open(files->filename, O_CREAT
				| files->o_flags | O_WRONLY, 0664);
		if (lol->cmd_fdout < 0)
			return (perror(""), exit(1), 1);
		files = files->next;
	}
	return (0);
}

int	ft_open_in_file(t_cmd *lol, int *exit_val)
{
	t_file	*files;

	files = lol->in_files;
	while (files)
	{
		lol->cmd_fdin = open(files->filename, O_RDONLY);
		if (files->o_flags == O_APPEND)
			ft_heredoc(lol, files->filename);
		if (lol->cmd_fdin < 0)
		{
			(*exit_val) = 1;
			return (perror(""), 1);
		}
		files = files->next;
	}
	return (0);
}
