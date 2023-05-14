#include <Minishell.h>


int ft_built_in_first(t_cmd *lol, char ***myenv, t_env **env_lst)
{
    if (lol->builtflag == CD)
		return (ft_cd(lol), 0);
	else if (lol->builtflag == EXT)
		ft_quit(NOT);
	else if (lol->builtflag == EXPT)
	{
		*myenv = ft_export(env_lst, lol->cmd[1], *myenv);
		return (0);
	}
	else if(lol->builtflag == UNST)
	{
		*myenv = ft_unset(&env_lst, lol->cmd[1], *myenv);
        return (0);
	}
    return (1);
}


int ft_child(t_cmd *lol, int *fd, t_env *env_lst, char **myenv)
{
    close(fd[0]);
		if (lol->out_files)
		{
			ft_open_out_files(lol);
			dup2(lol->cmd_fdout, STDOUT_FILENO);
		}
		else
			dup2(fd[1], STDOUT_FILENO);

		if (lol->builtflag)
		{
			ft_builtin(lol, env_lst, myenv);
			exit (0);
		}
		else if (lol->builtflag == NOT)
		{
			if ((execve(lol->cmd_path, lol->cmd, myenv) < 0) && !lol->builtflag)
			{
				perror("cmd doesn't exist");
				exit(1);
			}
			exit(0);
		}
}

int ft_parent(t_cmd *lol, int *fd, int *pid)
{
    close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		if (lol->cmd_fdin)
			close(lol->cmd_fdin);
		if (lol->last_cmd)
		{
			char	*line;
			while ((line = get_next_line(fd[0])))
				write(STDOUT_FILENO, line, ft_strlen(line));
		}
		waitpid(pid, NULL, 0);
		close (fd[0]);
}

int	ft_fork(t_cmd *lol, char ***myenv, t_env **env_lst)
{
	int	pid;
	int fd[2];

	if (!ft_built_in_first(lol, myenv, env_lst))
        return (0);
	if (lol->in_files)
	{
		ft_open_in_file(lol);
		dup2(lol->cmd_fdin, STDIN_FILENO);
	}
	pipe(fd);
	pid = fork();
	if (pid == 0)
        ft_child(lol, fd, *env_lst, *myenv);
	else
        ft_parent(lol, fd, pid);
	return 0;
}