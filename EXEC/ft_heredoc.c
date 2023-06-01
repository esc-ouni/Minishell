/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 18:27:11 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/01 10:49:18 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*hd_expand(char *line, t_nrm *nrm, t_collector **collector)
{
	int		i;
	char	*str;
	char	**s;

	str = NULL;
	if(!line)
		return (line);
	i = 0;
	s = ft_msplit(collector, line, '$');
	if (line[0] == '$')
	{
		str = ft_getenv(collector, s[i++], nrm->env);
	}
	return (str);	
}

static int	ft_heredoc_child(int *fd, char *delimiter, t_collector **collector, t_nrm *nrm)
{
	char	*line;
	char	*delim;

	signal(SIGQUIT, sig_hdandle);
	signal(SIGINT, sig_hdandle);
	delim = ft_strjoin(delimiter, "\n");
	close (fd[0]);
	line = get_next_line(0);
	while (line)
	{
		if (!ft_strncmp(line, delim, ft_strlen(line)))
		{
			free(line);
			exit(0);
		}
		line = hd_expand(line, nrm, collector);
		write(fd[1], line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
	}
	free(delim);
	exit(0);
	return (0);
}

int	ft_heredoc(t_cmd *cmd, char *delimiter, t_collector **collector, t_nrm *nrm)
{
	int		pid;
	int		fd[2];

	dup2(cmd->tty_in, STDIN_FILENO);
	pipe(fd);
	pid = fork();
	if (!pid)
	{
		ft_heredoc_child(fd, delimiter, collector, nrm);
	}
	else
	{
		close(fd[1]);
		cmd->cmd_fdin = dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
		close(fd[0]);
	}
	return (0);
}
