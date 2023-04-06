/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 18:35:34 by msamhaou          #+#    #+#             */
/*   Updated: 2023/04/04 18:40:29 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_process(char *line, char **env)
{
	int	pid;
	int	fd[2];
	int	readead_bytes;
	char buff[5];

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		ft_execute(line, env);
	}
	else
	{
		close (fd[1]);
		waitpid(pid, NULL, 0);
		while ((readead_bytes = read(fd[0], buff, 5)) > 0)
			write(STDOUT_FILENO, buff, 5);
	}
}

int main(int ac, char **av, char **env)
{
	char *r;
	while (1)
	{
		printf(">>");
		r = readline("");
		ft_process(r, env);
		// ft_execute(r, env);
	}
}