/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:58:42 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/14 13:54:00 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <termios.h>
# include <errno.h>
# include "libft.h"

typedef struct s_file		t_file;
typedef struct s_collector	t_collector;
typedef struct s_cmd		t_cmd;
typedef struct s_exp		t_exp;
typedef struct s_envlst		t_envlst;
typedef struct s_struct		t_struct;
int							g_var;

typedef enum e_built
{
	NOT,
	SYS,
	ECH,
	CD,
	PWD,
	EXPT,
	UNST,
	ENV,
	EXT
}	t_built;

struct s_file
{
	char		*filename;
	int			islast;
	int			o_flag;
	t_file		*next;
};

struct s_cmd
{
	char	**cmd;
	char	*cmd_path;
	t_file	*in_files;
	t_file	*out_files;
	int		fd_in;
	int		fd_out;
	int		*pipe_fd;
	t_built	builtflag;
	t_cmd	*next;
};

struct s_exp
{
	char	*str;
	t_exp	*next;
};

struct s_envlst
{
	char		*str;
	t_envlst	*next;
};

struct s_struct
{
	char		**env;
	t_envlst	*envlst;
	t_exp		*exp;
	t_cmd		*cmd;
	int			tmp_fd_in;
	int			tmp_err;
	int			exit_val;
	int			shlvl;
	int			is_heredoc;
	int			cmd_numb;
	t_collector	**collector;
};

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

typedef struct s_files
{
	t_file		*out_files;
	t_file		*in_files;
}	t_files;

typedef struct s_mlist
{
	char			*cmd;
	struct s_mlist	*next;
}	t_mlist;

typedef struct s_lexer
{
	char			*cmd;
	t_enum			type;
	struct s_lexer	*next;
}	t_lexer;

typedef struct s_ntmp
{
	void			*ntmp_addr;
	struct s_ntmp	*next;
}	t_ntmp;

typedef struct s_tmp
{
	void			*tmp_addr;
	struct s_tmp	*next;
}	t_tmp;

struct s_collector
{
	t_tmp				*tmp_cltr;
	t_ntmp				*ntmp_cltr;
};

typedef enum e_flag
{
	TMP,
	NTMP,
	ALL
}	t_flag;

void		ft_close_fdtmp(t_struct *cable);
void		ft_close(t_struct *cable, int fd);
int			ft_open_in_file(t_cmd *cmd, t_struct *cable);
void		ft_print_envlst(t_envlst *envlst);
void		ft_print_exp(t_exp *exp);
void		set_exitval(t_struct *cable, int extval);
void		get_sig_exitval(t_struct *cable, int extval);
void		ft_set_env_lst(t_struct *cable, char **ev);
void		ft_set_shlvl(t_struct *cable);
void		ft_env_set(t_struct *cable);
t_envlst	*ft_env_new_node(char *str, t_struct *cable);
t_envlst	*ft_last_envlst(t_envlst *envlst);
void		ft_env_add_back(t_envlst **envlst, t_envlst *toadd);
int			ft_export_env(t_struct *cable, char	*str);
void		ft_export_exp(t_struct *cable, char *str);
t_exp		*ft_exp_new_node(char *str, t_struct *cable);
t_exp		*ft_last_explst(t_exp *envlst);
void		ft_exp_add_back(t_exp **envlst, t_exp *toadd);
void		ft_exp_set(t_struct *cable);
size_t		ft_envlst_size(t_envlst *envlst);
void		ft_exec(t_struct *cable);
int			pcheck_tail(t_lexer **h_lexer);
int			pcheck_head(t_lexer **h_lexer);
int			pcheck_bdy(t_lexer **h_lexer);
void		ft_export(t_struct *cable, char	*str);
t_envlst	*ft_var_env_exist(t_envlst *envlst, char *str, t_struct *cable);
t_exp		*ft_var_exp_exist(t_exp *exp, char *str, t_struct *cable);
char		**ft_msoft_split_include(char *str, char c, t_struct *cable);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_trim_char(char *str, char c, t_struct *cable);
int			ft_child(t_cmd *cmd, int *fd, t_struct *cable);
int			ft_set_path(t_cmd *cmd, t_struct *cable);
int			ft_heredoc_proc(t_file *file, t_struct *cable);
void		ft_skip_env_node(t_struct *cable, t_envlst *exist);
void		ft_unset_envlst(t_struct *cable, char *str);
void		ft_skip_exp_node(t_struct *cable, t_exp *exist);
void		ft_unset_exp(t_struct *cable, char *str);
void		ft_print_var_err(char *str, int type);
void		ft_env_update(t_struct *cable);
char		*ft_getcwd(t_struct *cable);
int			ft_fork(t_cmd *cmd, t_struct *cable);
void		ft_joint_to_export(t_struct *cable, char **str);
int			ft_isplus(char *str, t_struct *cable);
void		ft_unset(t_struct *cable, char *str);
int			ft_cd(t_cmd *cmd, t_struct *cable);
void		ft_quit(t_cmd *cmd);
void		ft_print_err(char *str, int type);
int			ft_cd(t_cmd *cmd, t_struct *cable);
int			ft_echo(t_cmd *lol, t_struct *cable);
int			ft_pwd(t_struct *cable);
int			ft_builtin(t_cmd *lol, t_struct *cable);
void		free_tmp(t_collector **collector);
void		free_ntmp(t_collector **collector);
void		head_alloc(t_collector **collector);
void		tmp_alloc(t_collector **collector, size_t s, void **p);
void		ntmp_alloc(t_collector **collector, size_t s, void **p);
void		*h_malloc(t_collector **collector, size_t s, void *p, t_flag flag);
void		ft_collectorclear(t_collector **collector, t_flag flag);
char		**ft_msplit(t_struct *cable, char const *s, \
				char const c, t_flag flag);
char		*ft_mstrdup(t_struct *cable, const char *s1, \
				t_flag flag);
char		*ft_mstrjoin(t_struct *cable, char const *s1, \
				char const *s2, t_flag flag);
char		*ft_mstrtrim(t_struct *cable, char const *s1, \
				char const *set, t_flag flag);
char		*ft_getenv(t_struct *cable, char *key);
char		*ft_mitoa(t_struct *cable);
char		*ft_msubstr(t_struct *cable, char const *s, \
				unsigned int start, size_t len);
void		sig_h(int sig);
void		strt2(t_struct *cable);
void		strt1(t_struct *cable);
void		signal_dfl(void);
int			spc_after_d(char *line);
void		s_expa2(t_struct *cable, char *s, char **str);
void		s_expa(t_struct *cable, char *s, char **str);
void		signal_dfl(void);
void		emplify(t_struct *cable, t_cmd *cmd);
void		update_in_out_files(t_file *out_files, t_file *in_files);
void		check_for_in_files(t_struct *cable, t_file **in_files, t_lexer *n);
void		check_for_out_files(t_struct *cable, t_file **out_files, \
				t_lexer *n);
t_cmd		*get_cmd(t_struct *cable);
void		prm(int argc, char **argv, char **env);
void		strt(t_struct *cable);
int			check_syntax(t_struct *cable, char *s);
void		syntx_err(void);
int			check_pipes(t_lexer	**h_lexer);
int			searcher_for_spc(char *s);
int			check_oerr(char *s);
int			check_syntax2(t_lexer	**h_lexer);
void		set_exitval(t_struct *cable, int extval);
void		check_for_in_files(t_struct *cable, t_file **in_files, \
				t_lexer *n);
void		check_for_out_files(t_struct *cable, t_file **out_files, \
				t_lexer *n);
void		get_full_cmd(t_struct *cable, t_lexer **n, char ***full_cmd);
void		parser_init(t_file **out_files, t_file **in_files, \
				char ***full_cmd);
void		update_in_out_files(t_file *out_files, t_file *in_files);
void		whsp_lex(t_struct *cable, t_lexer **l_node, char *s, int *i);
void		pip_lex(t_struct *cable, t_lexer **l_node, char *s, int *i);
void		rot_lex(t_struct *cable, t_lexer **l_node, char *s, int *i);
void		roa_lex(t_struct *cable, t_lexer **l_node, char *s, int *i);
void		rin_lex(t_struct *cable, t_lexer **l_node, char *s, int *i);
void		rhd_lex(t_struct *cable, t_lexer **l_node, char *s, int *i);
void		emplify(t_struct *cable, t_cmd *cmd);
t_mlist		*ft_mlstnew(t_struct *cable, char *s);
t_built		cmd_type(t_struct *cable, char *cmd);
char		*prompt(void);
t_lexer		*parser(t_struct *cable, char *s);
void		debug(void);
void		expander(t_struct *cable, t_lexer **head);
t_cmd		*parser2(t_struct *cable, t_lexer *head);
void		after_parse2(t_cmd *cmd);
t_lexer		*lexer(t_struct *cable, char *s);
t_mlist		*ft_mlstlast(t_mlist *lst);
int			ft_mlstsize(t_mlist *lst);
void		ft_mlstadd_back(t_mlist **lst, t_mlist *new);
void		ft_mlstadd_front(t_mlist **lst, t_mlist *new);
void		ft_mlstclear(t_mlist **lst);
void		add_file_node(t_struct *cable, t_file **head, \
char *filename, int flag);
void		add_file_file(t_struct *cable, t_file **head, t_file *file);
void		add_to_cmd(t_struct *cable, t_cmd **head, char **full_cmd, \
t_files *files);
void		add_to_fullcmd(t_struct *cable, char ***full_cmd, \
t_lexer *n, int j);
void		add_lexer(t_struct *cable, t_lexer **head, char *content, \
				t_enum	type);
int			ft_cmdsize(t_cmd *cmd);
int			basic_syntax_check(t_lexer **h_lexer);
int			check_str(char *s);
void		check_for_rin(t_struct *cable, t_file **in_files, t_lexer **n);
void		check_for_hd(t_struct *cable, t_file **in_files, t_lexer **n);
int			basic_syntax_check2(t_lexer **h_lexer);
char		*s_expander(t_struct *cable, char *line);
void		expand_ev(t_struct *cable, char **str, char *s);
void		expand_evs(t_struct *cable, char *s, char **str);
void		expnd_v(t_struct *cable, t_lexer *node, char **str);
void		expnd_2(t_struct *cable, t_lexer *node, char **str);
void		printTYPE(t_enum num);
void		ft_alpha_order(t_struct *cable);
char		*ft_exported_str(char *str, t_struct *cable);
void		ft_export_exp(t_struct *cable, char *str);
int			ft_valid_var(const char *str);
char		**ft_soft_split(char *str, char c, t_struct *cable);

#endif
