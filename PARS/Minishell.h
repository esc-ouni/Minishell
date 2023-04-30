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
	// enum builtin	builtflag;
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

typedef enum e_enum
{
	STD,
    PIP,
    RED,
    ERO,
    SQU,
    DQU,
}	t_enum;

typedef struct s_list
{
    char            **full_cmd;
    char            *cmd;
    int             type;
    int             input;
    int             output;
    struct s_list   *next;
}   t_list;

void    prompt(void);
void    start(void);
t_list  *parser(void);
int     check_syntax(char *s);
t_cmd  *parser2(t_list *head);
void    after_parse2(t_cmd  *cmd);
void    after_parse(t_list  *head);
void	check_type(t_list	*node);
t_list	*ft_lstnew(char *s);
t_list	*ft_lstlast(t_list *lst);
int	    ft_lstsize(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *head,t_list *lst);
void	ft_lstclear(t_list **lst);

# endif
