/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 11:08:05 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/02 11:28:05 by msamhaou         ###   ########.fr       */
/*                                                                            */
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

typedef struct s_infile		t_infile;
typedef struct s_collector	t_collector;
typedef struct s_friw		t_friw;
typedef struct s_cmd		t_cmd;
typedef struct s_exp		t_exp;
typedef struct s_envlst		t_envlst;
typedef struct s_struct		t_struct;

struct s_infile
{
	char		*file_name;
	int			o_flag;
	t_infile	*next;
};

struct s_collector
{

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

void	ft_set_env_lst(t_struct *cable, char **ev);
void	ft_env_set(t_struct *cable, char **ev);

#endif
