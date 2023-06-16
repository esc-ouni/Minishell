/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_10.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:08:28 by idouni            #+#    #+#             */
/*   Updated: 2023/06/16 13:47:42 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syntax(t_struct *cable, char *s)
{
	if (!s)
	{
		write(1, "exit\n", 6);
		ft_close_fdtmp(cable);
		ft_collectorclear(cable->collector, ALL);
		exit (0);
	}
	if (!ft_strlen(s))
		return (2);
	if (check_str(s))
		return (1);
	add_history(s);
	if (check_oerr(s))
		return (1);
	return (0);
}

void	ninety_check(t_struct *cable, t_cmd *cmd)
{
	if (cmd)
	{
		if (!cmd->out_files && !cmd->in_files && !cmd->cmd)
		{
			cmd = NULL;
			return (ft_collectorclear(cable->collector, TMP));
		}
		else if (!cmd->out_files && !cmd->in_files \
		&& !cmd->cmd && (ft_cmdsize(cmd) > 1))
		{
			cmd = NULL;
			return (set_exitval(cable, 258), syntx_err(), \
			ft_collectorclear(cable->collector, TMP));
		}
	}
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
	ninety_check(cable, cmd);
	return (cmd);
}

char	*prompt(void)
{
	char	*s;

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
