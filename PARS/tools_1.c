/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:32:34 by idouni            #+#    #+#             */
/*   Updated: 2023/04/04 14:32:56 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// # include "minishell_pars.h"
#include "Minishell.h"


// void	check_type(t_list	*node)
// {
// 	if (!ft_strncmp(node->cmd, "|", 1))
// 		node->type = PIP;
// 	else if (!ft_strncmp(node->cmd, ";", 1))
// 		node->type = ERO;
// 	else if (!ft_strncmp(node->cmd, ">", 1))
// 		node->type = RED;
//     else if (!ft_strncmp(node->cmd, ">>", 2))
// 		node->type = RED;
//     else if (!ft_strncmp(node->cmd, "<", 1))
// 		node->type = RED;
//     else if (!ft_strncmp(node->cmd, "<<", 2))
// 		node->type = RED;
// 	else if (!ft_strncmp(node->cmd, "\'", 1))
// 		node->type = SQU;
// 	else if (!ft_strncmp(node->cmd, "\"", 1))
// 		node->type = DQU;
// 	else
// 		node->type = STD;
// }

void    prompt()
{
    // rl_redisplay();
    printf("\x1B[34m");
    printf("\nWHAT_YOU_WANT_MASTER>> ");
    printf("\x1B[0m");
    rl_on_new_line();
    // rl_redisplay();
}


// void    start()
// {
//     char    *s;
//     int     fd;

//     fd = open("header.h", O_RDONLY);
//     printf("\x1B[32m");
//     while ((s = get_next_line(fd)))
// 	{
//         printf("%s", s);
// 		free(s);
// 	}
//     printf("\x1B[0m");
//     printf("\n\n");
//     close(fd);
// }

void	free_collect(t_collector **collect_head)
{
	t_collector *tmp;
	t_collector *tmp2;
	tmp = *collect_head;

	while (tmp)
	{
		tmp2 = tmp->next;
		free(tmp);
		tmp = NULL;
		tmp = tmp2;
	}
}

void	*h_malloc(t_collector **collect_head, size_t s, void *p)
{
	t_collector *tmp;
    t_collector *new_node;
	new_node = malloc(sizeof(t_collector));
	p = malloc(s);
	if (!new_node || !p)
	{
		exit (1);
	}
	new_node->addr = p;
    if (!(*collect_head))
    {
        *collect_head = new_node;
        new_node->next = NULL;
    }
    else
    {
        tmp = *collect_head;
        while (tmp->next)
        {
            tmp = tmp->next;
        }
        tmp->next = new_node;
        new_node->next = NULL;
    }
	return (p);
}

int	check_dq(char *s)
{
	int i = 0;
	int c = 0;
	while (s[i])
	{
		if (s[i] == '"')
			c++;
		i++;
	}
	return ((c % 2));
}

int	check_sq(char *s)
{
	int i = 0;
	int c = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			c++;
		i++;
	}
	return ((c % 2));
}

int	check_oerr(char *s)
{
	int i = 0;
	int sq = 0;
	int dq = 0;

	while (s[i])
	{
		if (s[i] == '\'')
		{
			sq++;
			i++;
			while (s[i] != '\'' && s[i])
				i++;
			if (s[i] == '\'')
			{
				sq++;
				i++;
			}
		}
		else if (s[i] == '"')
		{
			dq++;
			i++;
			while (s[i] != '"' && s[i])
				i++;
			if (s[i] == '"')
			{
				dq++;
				i++;
			}
		}
		else
			i++;
	}
	if ((sq % 2) || (dq % 2))
		return (1);
	return (0);
}

int	check_syntax(char *s)
{
	if (!s)
		write(1, "exit\n", 5), exit(0);
	if (!ft_strlen(s))
		return (1);
	add_history(s);
	if (check_oerr(s))
		return (1);
	return (0);
}
