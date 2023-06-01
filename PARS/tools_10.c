/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_10.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:08:28 by idouni            #+#    #+#             */
/*   Updated: 2023/06/01 17:49:19 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_syntax(t_collector **collector, char *s, t_init *init)
{
	int	err;

	err = 0;
	if (!s)
	{
		write(1, "exit\n", 5);
		ft_collectorclear(collector);
		exit (0);
	}
	else if (!ft_strlen(s))
		err = 1;
	if (check_str(s))
		err = 1;
	add_history(s);
	if (check_oerr(s))
		err = 1;
	if (check_pipes(s))
		err = 1;
	if (err == 1)
	{
		ft_collectorclear(collector);
		return (1);
	}
	return (0);
}

char	*prompt(void)
{
	char	*s;

	rl_on_new_line();
	s = readline("BAASH >> ");
	return (s);
}

int	check_for_udf(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '&' || s[i] == ';')
			return (1);
		i++;
	}	
	return (0);
}

int	basic_syntax_check2(t_lexer **h_lexer)
{
	t_lexer	*node;

	node = *h_lexer;
	while (node)
	{
		if (node->type == SCMD && check_for_udf(node->cmd))
			return (syntx_err(), 1);
		node = node->next;
	}
	return (0);
}

int	check_syntax2(t_lexer **h_lexer)
{
	if (basic_syntax_check(h_lexer))
		return (1);
	else if (basic_syntax_check2(h_lexer))
		return (1);
	return (0);
}
