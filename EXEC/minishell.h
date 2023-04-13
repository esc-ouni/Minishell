
#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

typedef struct s_cmd
{
    char    **cmd;
    char    *input_file;
    int cmd_pos;
    int first_cmd;
    int last_cmd;
    int cmd_fdin;
    int inputed;
    int cmd_fdout;
    int *fd;
    struct s_cmd *next;
}   t_cmd;

int	ft_execute(char *arg, char **env);

#endif
