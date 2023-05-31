/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tool_plus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 18:17:45 by msamhaou          #+#    #+#             */
/*   Updated: 2023/05/30 20:55:26 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_quote_one(char *str)
{
	char	*quoted;

	quoted = ft_strjoin(ft_strdup("declare -x "), str);
	quoted = ft_strjoin(quoted, "\"\"");
	return (quoted);
}

static char	*ft_quote_two(char	**eq)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	char	*quoted;

	tmp = ft_strdup(eq[1]);
	tmp2 = ft_strdup(eq[0]);
	ft_free_stringp(eq);
	tmp3 = tmp2;
	tmp2 = ft_strjoin(ft_strdup("declare -x "), tmp3);
	free(tmp3);
	quoted = ft_strjoin(tmp2, "=");
	tmp2 = tmp;
	tmp = ft_strjoin(ft_strdup("\""), tmp);
	free(tmp2);
	tmp = ft_strjoin(tmp, "\"");
	quoted = ft_strjoin(quoted, tmp);
	free(tmp);
	return (quoted);
}

char	*ft_quote_it(char *to_quote)
{
	char	*quoted;
	char	**eq;

	if (ft_strchr(to_quote, '='))
	{
		eq = ft_split(to_quote, '=');
		if (!eq[1])
			return (ft_free_stringp(eq), quoted = ft_quote_one(to_quote));
		else
			quoted = ft_quote_two(eq);
	}
	else
	{
		quoted = ft_strjoin(ft_strdup("declare -x "), to_quote);
	}
	return (quoted);
}

int	ft_valid_var(const char	*str, char c)
{
	char	*pstr;

	pstr = (char *)str;
	if (*pstr == '=' || *pstr == '+')
		return (1);
	while (*pstr && *pstr != '=')
	{
		if (((*pstr == c) && (*(pstr + 1) != '=')) \
		&& (!isalnum(*pstr) || *pstr != '_'))
			return (1);
		pstr++;
	}
	return (0);
}

void	ft_put_err(void)
{
	ft_putendl_fd("minishell: not a valid identifier", 2);
}
