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

# define PIP 11
# define RED 12
# define ERR 13
# define SQU 14
# define DQU 15

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

typedef struct s_list
{
    char            **full_cmd;
    char            *cmd;
    int             type;
    struct s_list   *next;
}   t_list;

typedef struct s_f_list
{
    char            **full_cmd;
    char            *cmd;
    int             type;
    int             input;
    int             output;
    struct s_f_list   *next;
}   t_f_list;

void    prompt(void);
void    start(void);
t_list  *parser(void);
void    check_syntax(t_list *head);
t_list  *after_parse(t_list  *head);
void	check_type(t_list	*node);
t_list	*ft_lstnew(char *s);
t_list	*ft_lstlast(t_list *lst);
int	    ft_lstsize(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst);

# endif
