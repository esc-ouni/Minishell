/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 20:55:46 by idouni            #+#    #+#             */
/*   Updated: 2023/04/02 20:55:49 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <fcntl.h>
# include "LIBF/libft.h"
# include "G_N_L/get_next_line.h"
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <signal.h>
# include <curses.h>
# include <term.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_file
{
	char            *filename;
	int				islast;
	int				o_flags; /*Append  O_TRUNC O_CREAT .... */
	struct s_file   *next;
}   t_file;

typedef enum e_enum
{
    PIP,
	ST_LT,
	ST_SQ,
	ST_DQ,
    R_OA,
    R_OT,
    R_IN,
    R_HD,
	FIL,
	UDF
}	t_enum;

typedef enum e_built
{
	NOT,
	ECH,
    CD,
    PWD,
    EXPT,
    UNST,
    ENV,
    EXT
}	t_built;

typedef struct s_cmd
{
	char			**myenv;
	char			**cmd;
	t_file			*in_files;
	t_file			*out_files;
	int				num_cmds;
	int				first_cmd;
	int				last_cmd;
	t_built			builtflag;
	int				init_stdin;
	int				cmd_fdin;
	char			*cmd_path;
	int				cmd_fdout;
	struct s_cmd   *next;
}	t_cmd;

typedef struct s_mlist
{
    char            *cmd;
    struct s_mlist   *next;
}   t_mlist;

typedef struct s_lexer
{
    char            *cmd;
    t_enum			type;
    struct s_lexer	*next;
}   t_lexer;

int     check_syntax(char *s);
void	emplify(t_collector **collector, t_cmd *cmd, char **env);
// void	*h_malloc(t_collector **collect_head, size_t s, void *p);
t_mlist	*ft_mlstnew(t_collector **collector, char *s);
char	*ft_strdup(t_collector **collector, const char *s1);
char	**mgetenv(t_collector **collector, char **env);
t_built	cmd_type(t_collector **collector, char *cmd);
void    prompt(void);
t_lexer	*parser(t_collector	**collector);
void	debug(void);
t_cmd  *parser2(t_collector	**collector, t_lexer *head);
void    after_parse2(t_cmd  *cmd);
t_lexer *lexer(t_collector **collector, char *s);
t_mlist	*ft_mlstlast(t_mlist *lst);
int	    ft_mlstsize(t_mlist *lst);
void	ft_mlstadd_back(t_mlist **lst, t_mlist *new);
void	ft_mlstadd_front(t_mlist **lst, t_mlist *new);
void	ft_collectorclear(t_collector **collector);
void	ft_mlstclear(t_mlist **lst);
void 	add_file_node(t_collector	**collector, t_file **head, char *filename, int flag);
void 	add_file_file(t_collector **collector, t_file **head, t_file *file);
void 	add_to_cmd(t_collector **collector, t_cmd **head, char **full_cmd, t_file *out_files, t_file *in_files);
void	add_to_fullcmd(t_collector	**collector, char ***full_cmd, t_lexer *n);
void	add_lexer(t_collector **collector, t_lexer **head, char *content, t_enum	type);
int		ft_cmdsize(t_cmd *cmd);
void	*h_malloc(t_collector **collect_head, size_t s, void *p);

# endif
