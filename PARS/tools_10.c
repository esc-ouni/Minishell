/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_10.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:08:28 by idouni            #+#    #+#             */
/*   Updated: 2023/06/10 10:49:49 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syntax(t_struct *cable, char *s)
{
	if (!s)
	{
		write(1, "exit\n", 6);
		ft_collectorclear(cable->collector, ALL);
		exit (0);
	}
	if (!ft_strlen(s))
		return (1);
	if (check_str(s))
		return (1);
	add_history(s);
	if (check_oerr(s))
		return (1);
	if (check_pipes(s))
		return (1);
	return (0);
}

t_cmd	*get_cmd(t_struct *cable)
{
	char		*s;
	t_lexer		*h_lexer;
	t_cmd		*cmd;

	cmd = NULL;
	s = prompt();
	h_lexer = parser(cable, s);
	cmd = parser2(cable, h_lexer);
	emplify(cable, cmd);
	g_var = 0;
	return (cmd);
}

char	*prompt(void)
{
	char	*s;

	rl_on_new_line();
	s = readline("BAASH$ ");
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
