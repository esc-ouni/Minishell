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

#ifndef MINISHELL_H
# define MINISHELL_H

#include <termios.h>
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

int		var;


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
	int				tty_in;
	t_file			*in_files;
	t_file			*out_files;
	int				first_cmd;
	int				last_cmd;
	t_built			builtflag;
	int				num_cmds;
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
	SCMD,
	WH_SP,
	ST_SQ,
	ST_DQ,
    R_OA,
    R_OT,
    R_IN,
    R_HD,
	FIL_NM,
	UDF
}	t_enum;
enum    flags
{
	SYS,
	BUILT
};

typedef struct s_collector
{
    void            *addr;
    struct s_collector   *next;
}   t_collector;

typedef struct s_init
{
	int			tmp_fd_in;
	int			tmp_fd_out;
	int			err_in;
	char		**myenv;
	t_env		*envlst;
    t_env       *exp_lst;
	t_cmd		*cmd;
}	t_init;

typedef struct s_lexer
{
    char            *cmd;
	t_enum			type;
    struct s_lexer	*next;
}   t_lexer;

typedef struct s_files
{
	t_file		*out_files;
	t_file		*in_files;
}	t_files;

int		ft_builtin(t_cmd *lol, t_init *init);
int		ft_open_out_files(t_cmd *lol);
// int		ft_open_in_file(t_cmd *lol);
int		ft_open_in_file(t_cmd *lol, int *g_exit_val);
// int		ft_fork(t_cmd *lol, t_init *init);
int	ft_fork(t_cmd *lol, t_init *init, int *g_exit_val);
int		ft_execute(char *arg, char **env);
int		ft_cd(t_cmd *lol);
char	*ft_getcwd();
int		ft_pwd();
int		ft_echo(t_cmd *lol);
t_env   *ft_set_export_lst(t_env *env_lst);
char	**ft_export(t_init *init, char *str);
char    **ft_unset(t_init *init, char *str);
char	**ft_make_double_char(t_env *env_lst);
void	ft_free_stringp(char **env);
void	ft_free_pos(char **strp, int pos);
char	**ft_set_env(t_env *env_lst);
void	ft_sort_env(t_env *envlst);
void	env_add_back(t_env **env, t_env *toadd);
t_env	*ft_set_env_list(char **env);
size_t	ft_env_size(t_env *myenv);
int		ft_built_in_first(t_cmd *lol, t_init *init);
t_env	*new_env(char *str);
void	ft_env(char **myenv);
char	*ft_get_path(char **cmd, char **env);
void	sig_handle(int sig);
void	ft_quit(t_built flag, t_init *init);
int		ft_heredoc(t_cmd *cmd, char *delimiter);
void	ft_free_env_lst(t_env **env_lst);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_printlst(t_env *lst);
int		ft_heredoc(t_cmd *cmd, char *delimiter);
char	*ft_quote_it(char *to_quote);
void	ft_replace_exp_str(t_env *to_rep, char *str);
int		ft_trim_len(const char *str, char c);
int		ft_len_skip(char *str, char c);
char	*ft_trim_char(char *str, char c);
void	ft_exp_add_back(t_env **env, char *str);
int		ft_valid_var(const char	*str, char c);
t_env	*ft_exp_var_exist(t_env *exp, char *str);
void	ft_end_free(t_env **env_lst, char **myenv, t_init *init_val);
void	ft_put_err(void);
void	ft_norm_sucks(int ac, char **av);
t_init	*ft_init(t_collector **collector, char **env);
void	reset_io(t_collector **collector, t_init *inval);
void	strt(t_collector **collector);

// void    start(void);
// int     check_syntax(char *s);
// void    after_parse(t_mlist  *head);
// t_cmd    *after_parse(t_list  *head);
// void	check_type(t_list	*node);
char	*ft_getenv(t_collector **collector, char *key, t_env **menv);
void	*h_malloc(t_collector **collect_head, size_t s, void *p);
char	**ft_msplit(t_collector **collector, char const *s, char const c);
char	*ft_mstrdup(t_collector **collector, const char *s1);
char	*ft_mitoa(t_collector **collector, int n);
char	*ft_mstrjoin(t_collector **collector, char const *s1, char const *s2);
char	*ft_msubstr(t_collector **collector, char const *s, \
unsigned int start, size_t len);
char	*ft_mstrtrim(t_collector **collector, char const *s1, char const *set);

int		check_syntax(t_collector **collector, char *s, t_init *init);
void	syntx_err(void);
int		check_pipes(char *s);
int		searcher_for_spc(char *s);
int		check_oerr(char *s);
void	update_cmd(t_cmd *cmd);
int		check_syntax2(t_lexer	**h_lexer);
void	check_for_in_files(t_collector **collector, t_file **in_files, \
t_lexer *n);
void	check_for_out_files(t_collector **collector, t_file **out_files, \
t_lexer *n);
void	get_full_cmd(t_collector **collector, t_lexer **n, char ***full_cmd);
void	parser_init(t_file **out_files, t_file **in_files, char ***full_cmd);
void	update_in_out_files(t_file *out_files, t_file *in_files);
void	whsp_lex(t_collector **collector, t_lexer **l_node, char *s, int *i);
void	pip_lex(t_collector **collector, t_lexer **l_node, char *s, int *i);
void	rot_lex(t_collector **collector, t_lexer **l_node, char *s, int *i);
void	roa_lex(t_collector **collector, t_lexer **l_node, char *s, int *i);
void	rin_lex(t_collector **collector, t_lexer **l_node, char *s, int *i);
void	rhd_lex(t_collector **collector, t_lexer **l_node, char *s, int *i);

void printTYPE(t_enum num) ;
int	basic_syntax_check(t_lexer **h_lexer);
int	check_str(char *s);
// void	expnd_v(t_collector **collector, t_env **env, t_lexer *node, char **str);
void	expnd_v(t_collector **collector, t_env **env, t_lexer *node, char **str, int *g_exit_val);
// void	expnd_2(t_collector **collector, t_env **env, t_lexer *node, char **str);
void	expnd_2(t_collector **collector, t_env **env, t_lexer *node, char **str, int *g_exit_val);

void	emplify(t_collector **collector, t_cmd *cmd);
t_mlist	*ft_mlstnew(t_collector **collector, char *s);
char	*ft_mstrdup(t_collector **collector, const char *s1);
t_built	cmd_type(t_collector **collector, char *cmd);
char	*prompt(void);
// t_lexer	*parser(t_collector	**collector, t_env **env, char *s, t_init *init);
t_lexer	*parser(t_collector	**collector, t_env **env, char *s, t_init *init,  int *g_exit_val);
void	debug(void);
// void	expander(t_collector **collector, t_env **env, t_lexer **head);
void	expander(t_collector **collector, t_env **env, t_lexer **head, int *g_exit_val);
t_cmd	*parser2(t_collector **collector, t_lexer *head);
void	after_parse2(t_cmd *cmd);
t_lexer	*lexer(t_collector **collector, char *s);
t_mlist	*ft_mlstlast(t_mlist *lst);
int		ft_mlstsize(t_mlist *lst);
void	ft_mlstadd_back(t_mlist **lst, t_mlist *new);
void	ft_mlstadd_front(t_mlist **lst, t_mlist *new);
void	ft_collectorclear(t_collector **collector);
void	ft_mlstclear(t_mlist **lst);
void	add_file_node(t_collector	**collector, t_file **head, \
char *filename, int flag);
void	add_file_file(t_collector **collector, t_file **head, t_file *file);
void	add_to_cmd(t_collector **collector, t_cmd **head, char **full_cmd, \
t_files *files);
void	add_to_fullcmd(t_collector	**collector, char ***full_cmd, \
t_lexer *n, int j);
void	add_lexer(t_collector **collector, t_lexer **head, char *content, \
t_enum	type);
int		ft_cmdsize(t_cmd *cmd);
// void	*h_malloc(t_collector **collect_head, size_t s, void *p);

#endif
