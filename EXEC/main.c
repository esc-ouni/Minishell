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
	int	stdinit;

	stdinit = dup(0);

	lol = (t_cmd **)malloc(sizeof(t_cmd *) * 3);
	int i = 0;
	while (i < 3)
		lol[i++] = (t_cmd *)malloc(sizeof(t_cmd));
	lol[i] = NULL;
	//cmd 000
	lol[0]->cmd = ft_split("cat", ' ');
	lol[0]->cmd_path = "/bin/cat";
	lol[0]->input_file = "nnn.c";
	lol[0]->cmd_fdin = 0;
	lol[0]->inputed = 0;
	lol[0]->first_cmd = 1;
	lol[0]->last_cmd = 0;
	lol[0]->init_stdin = stdinit;

	//cmd 111
	lol[1]->cmd = ft_split("grep int", ' ');
	lol[1]->cmd_path = "/usr/bin/grep";
	lol[1]->input_file = NULL;
	lol[1]->first_cmd = 0;
	lol[1]->outputed = 0;
	lol[1]->last_cmd = 0;
	lol[1]->init_stdin = stdinit;
	lol[1]->next = NULL;

	//cmd 222
	lol[2]->cmd = ft_split("wc -l", ' ');
	lol[2]->cmd_path = "/bin/wc";
	lol[2]->input_file = NULL;
	lol[2]->first_cmd = 0;
	lol[2]->outputed = 0;
	lol[2]->last_cmd = 1;
	lol[2]->init_stdin = stdinit;
	lol[2]->next = NULL;
	return lol;
}


int	ft_fork(t_cmd **lol, char **env)
{
	int	fd[2];
	int	pid;
	int	i = 0;
	pipe(fd);

	while (i < 3)
	{
		//dup2(lol[i]->init_stdin, STDIN_FILENO);
		if (lol[i]->input_file)
		{
			lol[i]->cmd_fdin = open(lol[i]->input_file, O_RDONLY);
			if (lol[i]->cmd_fdin < 0)
				exit(1);
			dup2(lol[i]->cmd_fdin, STDIN_FILENO);
			// close(lol[i]->cmd_fdin);
		}
		else if(!lol[i]->input_file)
			dup2(fd[0], STDIN_FILENO);
		pid = fork();
		if (pid == 0)
		{
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
			execve(lol[i]->cmd_path, lol[i]->cmd, env);
		}
		else
		{
			close(fd[1]);
			//sleep(10);
			waitpid(pid, NULL, 0);
			if (lol[i]->cmd_fdin)
				close(lol[i]->cmd_fdin);
		}
		i++;
	}
	if (fd[0])
		close(fd[0]);
	if (fd[1])
		close(fd[1]);
}
int main(int ac, char **av, char **env)
{
	char *r;
	int	tmp_fd_in;
	int	tmp_fd_out;
	t_cmd	**lol;

	tmp_fd_in = dup(STDIN_FILENO);
	tmp_fd_out = dup (STDOUT_FILENO);

	lol = init();
	while (1)
	{
		dup2(tmp_fd_in, 0);
		dup2(tmp_fd_out, 1);
		printf(">>");
		r = readline("");
		ft_fork(lol, env);
		// ft_execute(r, env);
	}
}