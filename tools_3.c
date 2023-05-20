#include "Minishell.h"
static int	check(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	ns_start(char const *s1, char const *set)
{
	size_t		l_f;
	size_t		i;

	i = 0;
	l_f = 0;
	while (s1[i])
	{
		if (check(s1[i], set) == 1)
			l_f++;
		else
			break ;
		i++;
	}
	return (l_f);
}

static int	ns_end(char const *s1, char const *set)
{
	size_t		l_e;
	size_t		l;

	l_e = ft_strlen(s1) - 1;
	l = l_e;
	while (l)
	{
		if (check(s1[l_e], set) == 1)
			l_e--;
		else
			break ;
		l--;
	}
	return (l_e);
}

char	*ft_mstrtrim(t_collector **collector, char const *s1, char const *set)
{
	char		*ns;
	size_t		l;
	size_t		l_e;
	size_t		l_f;
	size_t		i;

	ns = NULL;
	i = 0;
	if (!s1 || !set)
		return (NULL);
	l_f = ns_start(s1, set);
	l_e = ns_end(s1, set);
	if (l_f > l_e)
		return (ft_mstrdup(collector, ""));
	l = l_e - l_f + 1;
	ns = (char *)h_malloc(collector, sizeof (char) * (l + 1), ns);
	if (!ns)
		return (0);
	while (l--)
	{
		ns[i] = s1[l_f + i];
		i++;
	}
	ns[i] = '\0';
	return (ns);
}

char	*ft_msubstr(t_collector **collector, char const *s, unsigned int start, size_t len)
{
	char	*ns;
	size_t	l;

	ns = NULL;
	if (s == NULL)
		return (NULL);
	if (start > (unsigned int)ft_strlen(s))
		return (ft_mstrdup(collector, ""));
	l = (unsigned int)ft_strlen(s + start);
	if (l < len)
		len = l;
	ns = (char *)h_malloc(collector, sizeof (char) * (len + 1), ns);
	if (!ns)
		return (NULL);
	ft_strlcpy(ns, s + start, len + 1);
	return (ns);
}
