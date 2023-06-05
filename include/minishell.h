/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taha <taha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 11:08:05 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/04 21:02:36 by taha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#ifndef	MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>
# include "libft.h"


typedef struct s_infile		t_file;
typedef struct s_collector	t_collector;
typedef struct s_friw		t_friw;
typedef struct s_cmd		t_cmd;
typedef struct s_exp		t_exp;
typedef struct s_envlst		t_envlst;
typedef struct s_struct		t_struct;

struct s_file
{
	char		*file_name;
	int			o_flag;
	t_file	*next;
};

struct s_friw
{
	t_collector	*tmp;
	t_collector	*end;
};

struct s_cmd
{
	char	**cmd;
	char	*cmd_path;
	t_file	*in_file;
	t_file	*out_file;
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
	t_friw		*friwi;
	int			exit_val;
	int			var;
	int			is_heredoc;
	int			cmd_numb;
};

typedef struct s_ntmp
{
    void            *ntmp_addr;
    struct s_ntmp	*next;
}   t_ntmp;

typedef struct s_tmp
{
    void           	*tmp_addr;
    struct s_tmp	*next;
}   t_tmp;

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

void	*h_malloc(t_collector **collector, size_t s, void *p, t_flag flag);
void	ft_collectorclear(t_collector **collector, t_flag flag);

void	ft_set_env_lst(t_struct *cable, char **ev);
void	ft_env_set(t_struct *cable);
t_envlst	*ft_env_new_node(char *str);
t_envlst	*ft_last_envlst(t_envlst *envlst);
void	ft_env_add_back(t_envlst **envlst, t_envlst *toadd);
t_exp	*ft_exp_new_node(char *str);
t_exp	*ft_last_explst(t_exp *envlst);
void	ft_exp_add_back(t_exp **envlst, t_exp *toadd);
void	ft_exp_set(t_struct *cable);
size_t	ft_envlst_size(t_envlst *envlst);
void	ft_exec(t_struct *cable);
void	ft_alpha_order(t_struct *cable);
char	*ft_exported_str(char *str);
void	ft_export_exp(t_struct *cable, char *str);
int		ft_valid_var(const char	*str);

#endif
