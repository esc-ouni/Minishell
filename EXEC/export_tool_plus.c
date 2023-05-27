/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tool_plus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 18:17:45 by msamhaou          #+#    #+#             */
/*   Updated: 2023/05/27 18:20:01 by msamhaou         ###   ########.fr       */
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
	char	*quoted;

	tmp = ft_strdup(eq[1]);
	tmp2 = ft_strdup(eq[0]);
	ft_free_stringp(eq);
	tmp2 = ft_strjoin(ft_strdup("declare -x "), tmp2);
	quoted = ft_strjoin(tmp2, "=");
	tmp2 = tmp;
	tmp = ft_strjoin(ft_strdup("\""), tmp);
	tmp = ft_strjoin(tmp, "\"");
	quoted = ft_strjoin(quoted, tmp);
	free(tmp);
	free(tmp2);
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
			return (quoted = ft_quote_one(to_quote));
		else
			quoted = ft_quote_two(eq);
	}
	else
	{
		quoted = ft_strjoin(ft_strdup("declare -x "), to_quote);
	}
	return (quoted);
}
