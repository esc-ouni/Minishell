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
    char            *cmd;
    struct s_list   *next;
}   t_list;

void    prompt(void);
void    start(void);
void    after_parse(t_list  **head);
t_list  **read_line(void);
t_list	*ft_lstnew(char *s);
t_list	*ft_lstlast(t_list *lst);
int	    ft_lstsize(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst);

# endif