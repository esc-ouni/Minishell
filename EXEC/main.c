/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 18:35:34 by msamhaou          #+#    #+#             */
/*   Updated: 2023/04/28 00:53:44 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	siglol = 0;

void	files_init(t_file **file)
{
	int	num_files = 1;
	int	i = 0;
	t_file	*head = (*file);

	while (i < num_files)
	{
		if (!(*file))
			(*file) = (t_file *)malloc(sizeof(t_file));
		(*file)->next = (t_file *)malloc(sizeof(t_file));
		(*file) = (*file)->next;
		i++;
	}
	(*file)->next = NULL;
	*file = head;

	/*file 1*/
	(*file)->filename = "out1.txt";
	/*file 2*/
	(*file)->next->filename = "out2.txt";


	//return(head);
}

t_cmd	**init(char	**env)
{
	t_cmd **lol;
	int	stdinit;
	char	**myenv;
	enum	flags;
	t_file	*files ;
	files_init(&files);

	myenv = ft_set_env(env);
	stdinit = dup(0);

	lol = (t_cmd **)malloc(sizeof(t_cmd *) * 3);
	int i = 0;
	while (i < 1)
		lol[i++] = (t_cmd *)malloc(sizeof(t_cmd));
	lol[i] = NULL;
	//cmd 000
	lol[0]->cmd = ft_split("pwd", ' ');
	lol[0]->env = myenv;
	//lol[0]->cmd_path = "/usr/bin/cat";
	lol[0]->cmd_flag = BUILT;
	lol[0]->builtflag = PWD;
	lol[0]->input_file = NULL;
	lol[0]->output_file = NULL;
	lol[0]->cmd_fdin = 0;
	lol[0]->inputed = 0;
	lol[0]->first_cmd = 1;
	lol[0]->last_cmd = 1;
	lol[0]->init_stdin = stdinit;
	lol[0]->out_files = files;
	return lol;
}

int	ft_builtin(t_cmd *lol)
{
	if (lol->builtflag == ECHO)
		ft_echo(lol);
	else if (lol->builtflag == CD)
		ft_cd(lol);
	else if (lol->builtflag == PWD)
		ft_pwd();
	else if (lol->builtflag == EXPORT)
		ft_export(lol->env, lol->cmd[1]);
	// else if (lol->builtflag == UNSET)
		
	// else if (lol->builtflag == ENV)
		
	// else if (lol->builtflag == EXIT)
		
	return(0);
}


int	ft_open_files(t_cmd *lol)
{
	t_file	*files;

	files = lol->out_files;
	while (files->next)
	{
		open(files->filename, O_CREAT | O_WRONLY , 0664);
		files = files->next;
	}
	lol->cmd_fdout = open(files->filename, O_CREAT | O_WRONLY , 0664);
	return (0);
}

int	ft_fork(t_cmd *lol, char **env)
{
	int	pid;
	int fd[2];

	if (lol->cmd_flag == BUILT && !ft_strncmp(lol->cmd[0], "cd", ft_strlen(lol->cmd[0])))
		return (ft_cd(lol), 0);
	if (lol->input_file)
	{
		lol->cmd_fdin = open(lol->input_file, O_RDONLY);
		if (lol->cmd_fdin < 0)
			exit(1);
		dup2(lol->cmd_fdin, STDIN_FILENO);
	}
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		if (lol->out_files)
		{
			ft_open_files(lol);
			dup2(lol->cmd_fdout, STDOUT_FILENO);
		}
		else
			dup2(fd[1], STDOUT_FILENO);

		if (lol->cmd_flag == BUILT)
		{
			ft_builtin(lol);
			exit (0);
		}
		else if (lol->cmd_flag == SYS)
			if (execve(lol->cmd_path, lol->cmd, env) < 0)
				return(perror(""), 1);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
		if (lol->cmd_fdin)
			close(lol->cmd_fdin);
		if (lol->last_cmd)
		{
			char buff[5];
			while (read(fd[0], buff, 5) > 0)
				write(STDOUT_FILENO, buff, 5);
		}
		close (fd[0]);
	}
	return 0;
}

void	ft_prompt()
{
	char	*pwd;
	char	*user;

	user = getenv("USER");
	pwd = ft_getcwd();
	printf("\e[1;35m%s:\e[0m\e[1;34m%s\e[0m$ ", user, pwd);
	free(pwd);
}

void	ft_free_pos(char **strp, int pos)
{
	while (pos--)
		free(strp[pos]);
	free(strp);
}

char	**ft_set_env(char **env)
{
	int		i;
	char	**res;

	i = 0;
	while (env[i])
		i++;
	res = (char **)malloc(sizeof(char *) * (i + 1));
	if (!res)
		return(perror(""), NULL);
	i = 0;
	while (env[i])
	{
		res[i] = ft_strdup(env[i]);
		if (!res[i])
			return (ft_free_pos(res, i), NULL);
		i++;
	}
	return(res);
}

/********************SIGNALES********************/
void	sig_handle(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);/*should be one after history setup*/
		rl_redisplay();
		ft_prompt();
		//siglol = 1;
	}
	else if(sig == SIGQUIT)
	{
		ft_prompt();
		rl_redisplay();
		write(1, "exit\n", 5);
		exit(0);
	}
}
/********************SIGNALES********************/

int main(int ac, char **av, char **env)
{
	(void)av;
	(void)ac;
	char	*r;
	int		tmp_fd_in;
	int		tmp_fd_out;
	t_cmd	**lol;
	int		i;
	
	i = 0;
	tmp_fd_in = dup(STDIN_FILENO);
	tmp_fd_out = dup (STDOUT_FILENO);
	lol = init(env);
	while (1)
	{
		i = 0;
		siglol = 0;
		dup2(tmp_fd_in, 0);
		dup2(tmp_fd_out, 1);
		ft_prompt();
		signal(SIGINT, sig_handle);
		signal(SIGQUIT, sig_handle);
		r = readline("");
		while (i < 1)
			ft_fork(lol[i++], env);
	}
}
