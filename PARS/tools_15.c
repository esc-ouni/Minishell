/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_15.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:09:45 by idouni            #+#    #+#             */
/*   Updated: 2023/06/08 14:46:33 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_dfl()
{
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
	{
		perror("Error handling a signal");
		exit(0);
	}
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
	{
		perror("Error handling a signal");
		exit(0);
	}
}

void	tail(t_struct *cable, char *line, char **str)
{
	if (line[ft_strlen (line) - 1] == '$')
		(*str) = ft_mstrjoin(cable, (*str), "$", TMP);
	free(line);
}

void	expns(t_struct *cable, char **s, char **str)
{
	int		i;

	i = 1;
	while (s[i])
	{
		s_expa2(cable, s[i], str);
		i++;
	}
}

char	*s_expander(t_struct *cable, char *line)
{
	char	**s;
	char	*str;

	str = NULL;
	s = NULL;
	if (!line)
		return (NULL);
	if (!ft_strchr(line, '$') || spc_after_d(line))
	{
		str = ft_mstrdup(cable, line, TMP);
		free(line);
		return (str);
	}
	s = ft_msplit(cable, line, '$', TMP);
	if (!s[0])
		return ("$");
	if (line[0] == '$')
		s_expa(cable, s[0], &str);
	else
		str = ft_mstrjoin(cable, str, s[0], TMP);
	expns(cable, s, &str);
	tail(cable, line, &str);
	return (str);
}

int	check_syntax2(t_lexer **h_lexer)
{
	if (basic_syntax_check(h_lexer))
		return (1);
	else if (basic_syntax_check2(h_lexer))
		return (1);
	return (0);
}
