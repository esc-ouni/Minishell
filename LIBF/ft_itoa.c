/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 12:52:30 by idouni            #+#    #+#             */
/*   Updated: 2023/06/06 20:11:29 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nbrlen(long n)
{
	int	i;

	i = 1;
	if (n < 0)
		n = -n;
	while (n > 9)
	{
		i++;
		n /= 10;
	}
	return (i);
}

static long	checker(long n)
{
	if (n < 0)
		n = -n;
	return (n);
}

static char	*putnbr(char *s, long n, int nc, int i)
{
	long	n2;

	s[i] = '\0';
	i++;
	n = checker(n);
	n2 = n;
	while (nc)
	{
		if (n < 10)
		{
			s[i] = (char)(n + 48);
			i++;
			break ;
		}
		else if (n >= 10)
		{
			n %= 10;
			s[i] = (char)(n + 48);
			i++;
		}
		n2 /= 10;
		n = n2;
		nc--;
	}
	return (s);
}

static char	*strevv(char *s, int end, int t)
{
	char	temp;
	int		start;

	start = 0;
	if (t == 1)
		s[end] = '-';
	while (start < end)
	{
		temp = s[start];
		s[start] = s[end];
		s[end] = temp;
		start++;
		end--;
	}
	return (s);
}

char	*ft_mitoa(t_collector **collector, int n)
{
	char		*s;
	int			i;
	int			t;
	int			nc;
	long		nn;

	s = NULL;
	i = 0;
	t = 0;
	nn = n;
	nc = nbrlen(nn) + 1;
	if (nn < 0)
	{
		nc += 1;
		t = 1;
	}
	s = (char *)h_malloc(cable->collector, sizeof (char) * nc, s);
	if (s == NULL)
		return (NULL);
	s = putnbr(s, nn, nc, i);
	s = strevv(s, nc - 1, t);
	return (s);
}
