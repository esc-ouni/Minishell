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
	int				islast; /*Append  O_TRUNC O_CREAT .... */
	struct s_file   *next;
}   t_file;

typedef struct s_cmd
{
	char			**env;
	char			**cmd;
	// enum builtin	builtflag;
	char			*cmd_path;
	int				first_cmd;
	int				last_cmd;
	t_file			*in_files;
	t_file			*out_files;
	struct s_cmd	*next;
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
    char            *cmd;
    struct s_list   *next;
}   t_list;

typedef struct s_lexer
{
    char            *cmd;
    struct s_lexer	*next;
}   t_lexer;

// void    start(void);
// int     check_syntax(char *s);
// void    after_parse(t_list  *head);
// t_cmd    *after_parse(t_list  *head);
// void	check_type(t_list	*node);
char	**mgetenv(char **env);
void    prompt(void);
t_lexer	*parser(void);
void	debug(void);
t_cmd  *parser2(t_lexer *head);
void    after_parse2(t_cmd  *cmd);
t_lexer *lexer(char *s);
t_list	*ft_lstnew(char *s);
t_list	*ft_lstlast(t_list *lst);
int	    ft_lstsize(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst);
void 	add_file_node(t_file **head, char *filename, int flag);
void 	add_file_file(t_file **head, t_file *file);
void 	add_to_cmd(t_cmd **head, char **full_cmd, t_file *out_files, t_file *in_files);
void	add_lexer(t_lexer **head, char *content);
int		ft_cmdsize(t_cmd *cmd);


# endif
