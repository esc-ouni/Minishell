/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 14:21:41 by idouni            #+#    #+#             */
/*   Updated: 2022/11/12 14:21:43 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_s(char **p, int l)
{
	while (l)
	{
		free(p[l]);
		l--;
	}
	free(p[0]);
	free(p);
	return (NULL);
}

static size_t	count_str(char const *s, char c)
{
	size_t	i;
	size_t	t;
	size_t	count;

	i = 0;
	t = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && t == 0)
		{
			t = 1;
			count++;
		}
		else if (s[i] == c)
			t = 0;
		i++;
	}
	return (count);
}

static size_t	lenfinder(char const *s, char c, int start)
{
	size_t	i;

	i = 0;
	while (s[start + i] || s[start + i] == '\0')
	{
		if (s[start + i] == c || s[start + i] == '\0')
			return (i);
		i++;
	}
	return (0);
}

static size_t	q_lenfinder(char const *s, char c, int start)
{
	size_t	i;

	(void)c;
	i = 0;
	while (s[start + i] || s[start + i] == '\0')
	{
		if (s[start + i] == '"' || s[start + i] == '\0')
			return (i);
		i++;
	}
	return (0);
}

static char	**ft_splitp2(char **p, char const *s, char const c)
{
	size_t		i;
	size_t		l;
	size_t		l_s;
	size_t		i2;

	i = 0;
	i2 = 0;
	l_s = ft_strlen(s);
	while (i < l_s)
	{
		if (s[i] == '"')
		{
			l = q_lenfinder(s, c, i);
			p[i2] = ft_substr(s, i, l);
			if (p[i2] == NULL)
				return (free_s (p, i2));
			i2++;
			i += l;
		}
		if (s[i] != c)
		{
			l = lenfinder(s, c, i);
			p[i2] = ft_substr(s, i, l);
			if (p[i2] == NULL)
				return (free_s (p, i2));
			i2++;
			i += l;
		}
		i++;
	}
	p[i2] = NULL;
	return (p);
}

char	**ft_split(char const *s, char const c)
{
	size_t		n;
	char		**p;

	if (!s)
		return (NULL);
	n = count_str(s, c);
	p = (char **)malloc(sizeof (char *) * (n + 1));
	if (p)
	{
		p = ft_splitp2(p, s, c);
		return (p);
	}
	return (NULL);
}
