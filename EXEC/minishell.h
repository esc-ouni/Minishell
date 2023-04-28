
#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <sys/types.h>
# include <dirent.h>
# include "libft/libft.h"

enum    flags
{
	SYS,
	BUILT
};

enum    builtin
{
	NOT,
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
};

typedef struct s_file
{
	char            *filename;
	int				o_flags; /*Append  O_TRUNC O_CREAT .... */
	struct s_file   *next;
}   t_file;

typedef struct s_cmd
{
	char			**env;
	char			**cmd;
	int				cmd_flag;
	char			*input_file;
	char			*output_file;
	enum builtin	builtflag;
	char			*cmd_path;
	int				cmd_pos;
	int				init_stdin;
	int				first_cmd;
	int				last_cmd;
	int				cmd_fdin;
	int				inputed;
	int				outputed;
	int				cmd_fdout;
	int				*fd;
	t_file			*in_files;
	t_file			*out_files;
}   t_cmd;

int	ft_execute(char *arg, char **env);
int     ft_cd(t_cmd *lol);
char    *ft_getcwd();
int     ft_pwd();
int	ft_echo(t_cmd *lol);
char	**ft_export(char **env, char *str);
void	ft_free_old_env(char **env);
void	ft_free_pos(char **strp, int pos);
char	**ft_set_env(char **env);

#endif
