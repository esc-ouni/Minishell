#include "Minishell.h"

char	*ft_mstrdup(t_collector **collector, const char *s1)
{
	size_t	i;
	char	*s;

	i = 0;
	s = NULL;
	if (!s1)
		return (NULL);
	s = (char *)h_malloc(collector, sizeof(char) * (ft_strlen(s1) + 1), s);
	while (s1[i] != '\0')
	{
		s[i] = s1[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*ft_mstrjoin(t_collector **collector, char const *s1, char const *s2)
{
	size_t		l1;
	size_t		l2;
	char		*ns;

	ns = NULL;
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	ns = (char *)h_malloc(collector, sizeof(char) * (l1 + l2 + 1), ns);
	if (ns)
	{
		if (s1)
			ft_memmove(ns, s1, l1);
		if (s2)
			ft_memmove(ns + l1, s2, l2);
		ns[l2 + l1] = '\0';
		return (ns);
	}
	return (ns);
}
