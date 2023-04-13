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

// int	ft_process(char *line, char **env)
// {
// 	int	pid;
// 	int	readead_bytes;
// 	char buff[5];

// 	ft_pipe_open();
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		close(fd[0]);
// 		dup2(fd[1], STDOUT_FILENO);
// 		ft_execute(line, env);
// 	}
// 	else
// 	{
// 		close (fd[1]);
// 		if (!last)
// 			dup2(fd[0], STDIN_FILENO);
// 		else
// 			while ((readead_bytes = read(fd[0], buff, 5)) > 0)
// 				write(STDOUT_FILENO, buff, 5);
// 		waitpid(pid, NULL, 0);
// 	}
// }

t_cmd	**init()
{
	t_cmd **lol;

	lol = (t_cmd **)malloc(sizeof(t_cmd *) * 3);
	int i = 0;
	while (i < 2)
		lol[i++] = (t_cmd *)malloc(sizeof(t_cmd));
	lol[i] = NULL;
	//cmd 000
	lol[0]->cmd = ft_split("ls -la", ' ');
	lol[0]->cmd_fdin = 0;
	lol[0]->inputed = 0;
	lol[0]->first_cmd = 1;
	lol[0]->last_cmd = 0;
	lol[0]->next = lol[1];

	//cmd 111
	lol[1]->cmd = ft_split("wc -l", ' ');
	lol[1]->first_cmd = 0;
	lol[1]->outputed = 0;
	lol[1]->last_cmd = 1;
	lol[1]->next = NULL;
	return lol;
}

int ft_pipe_open(t_cmd **lol)
{
	int i = 0;
	while (lol[i])
	{
		lol[i]->fd = (int *)malloc(sizeof(int) * 2);
		pipe(lol[i++]->fd);
	}
	return 0;
}

int	ft_redirect(t_cmd **lol)
{
	int i = 0;
	while (lol[i])
	{
		if (lol[i]->first_cmd)
		{
			if (lol[i]->inputed)
				lol[i]->cmd_fdin = open(lol[i]->input_file, O_RDONLY);
			else
				lol[i]->cmd_fdin = 0;
			lol[i]->cmd_fdout = lol[i]->next->fd[1];
		}
		else if(lol[i]->last_cmd)
		{
			if(lol[i]->outputed)
				lol[i]->cmd_fdout = open(lol[i]->output_file, O_WRONLY);
			else
				lol[i]->cmd_fdout = 1;
		}
		else
		{
			lol[i]->cmd_fdin = fd[1];
			
		}
		dup2(lol[i]->cmd_fdin, STDIN_FILENO);
	}
}

int main(int ac, char **av, char **env)
{
	char *r;
	t_cmd	**lol;

	lol = init();
	ft_pipe_open(lol);
	ft_redirect(lol);
	for (int i = 0 ;lol[i]; i++)
	{
		printf("%d %d \n", lol[i]->fd[0], lol[i]->fd[1]);
	}
	// while (1)
	// {
	// 	printf(">>");
	// 	r = readline("");
	// 	ft_process(r, env);
	// 	// ft_execute(r, env);
	// }
}