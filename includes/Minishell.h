/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_pars.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 20:55:46 by idouni            #+#    #+#             */
/*   Updated: 2023/04/02 20:55:49 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_PARS_H
# define MINISHELL_PARS_H
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <sys/types.h>
# include <dirent.h>
# include "libft.h"
# include "get_next_line.h"


typedef struct s_env
{
	char			*str;
	struct s_env	*next;
}	t_env;

typedef struct s_file
{
	char            *filename;
	int				o_flags; /*Append  O_TRUNC O_CREAT .... */
	int				islast;
	struct s_file   *next;
}   t_file;

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
	t_env			*myenv;
	char			**cmd;
	t_file			*in_files;
	t_file			*out_files;
	int				first_cmd;
	int				last_cmd;
	t_built			builtflag;
	//7odoud
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

enum    flags
{
	SYS,
	BUILT
};


typedef struct s_lexer
{
    char            *cmd;
	t_enum			type;
    struct s_lexer	*next;
}   t_lexer;

typedef struct s_collector
{
    void            *addr;
    struct s_collector   *next;
}   t_collector;

int	ft_builtin(t_cmd *lol, t_env *env_lst, char **myenv);
int	ft_fork(t_cmd *lol, char ***myenv, t_env **env_lst);
int	ft_execute(char *arg, char **env);
int     ft_cd(t_cmd *lol);
char    *ft_getcwd();
int     ft_pwd();
int	ft_echo(t_cmd *lol);
char	**ft_export(t_env **env_lst, char *str, char **myenv);
char    **ft_unset(t_env **env_lst, char *str, char **myenv);
void	ft_free_old_env(char **env);
void	ft_free_pos(char **strp, int pos);
char	**ft_set_env(t_env *env_lst, char **myenv);
t_env    *ft_set_env_list(char **env);
void	ft_env(char **myenv);
char	*ft_get_path(char **cmd, char **env);
void	sig_handle(int sig);
void	ft_quit(t_built flag);
// void    start(void);
// int     check_syntax(char *s);
// void    after_parse(t_mlist  *head);
// t_cmd    *after_parse(t_list  *head);
// void	check_type(t_list	*node);
void	*h_malloc(t_collector **collect_head, size_t s, void *p);
char    **ft_msplit(t_collector **collector, char const *s, char const c);
char	*ft_mstrdup(t_collector **collector,const char *s1);
char    *ft_mstrjoin(t_collector **collector, char const *s1, char const *s2);
char	*ft_msubstr(t_collector **collector, char const *s, unsigned int start, size_t len);
char	*ft_mstrtrim(t_collector **collector, char const *s1, char const *set);
int     check_syntax(char *s);
void	emplify(t_collector **collector, t_cmd *cmd, char **env);
t_mlist	*ft_mlstnew(t_collector **collector, char *s);
char	*ft_mstrdup(t_collector **collector, const char *s1);
char	**mgetenv(t_collector **collector, char **env);
t_built	cmd_type(t_collector **collector, char *cmd);
void    prompt(void);
t_lexer	*parser(t_collector	**collector);
void	debug(void);
void	expander(t_collector **collector, t_lexer **head);
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
