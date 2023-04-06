
#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

int	ft_execute(char *arg, char **env);

#endif
