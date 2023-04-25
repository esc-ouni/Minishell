
#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

enum    flags{
    SYS,
    BUILT
};

typedef struct s_file
{
    char *filename;
    int infile;
    int outfile;

}   t_file;

typedef struct s_cmd
{
    char    **cmd;
    int     cmd_flag;
    char    *input_file;
    char    *output_file;
    char    *cmd_path;
    int     cmd_pos;
    int     init_stdin;
    int     first_cmd;
    int     last_cmd;
    int     cmd_fdin;
    int     inputed;
    int     outputed;
    int     cmd_fdout;
    int     *fd;
    struct s_cmd *next;
}   t_cmd;

int	ft_execute(char *arg, char **env);
int     ft_cd(t_cmd *lol);
char    *ft_getcwd();
int     ft_pwd();
int	ft_echo(t_cmd *lol);
char	**ft_export(char **env, char *str);
void	ft_free_old_env(char **env);
void	ft_free_pos(char **strp, int pos);

#endif
