/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_11.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:09:45 by idouni            #+#    #+#             */
/*   Updated: 2023/06/05 12:12:09 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*ft_mitoa(t_struct *cable)
{
	char		*s;
	int			i;
	int			t;
	int			nc;
	long		nn;

	s = NULL;
	i = 0;
	t = 0;
	nn = cable->exit_val;
	nc = nbrlen(nn) + 1;
	if (nn < 0)
	{
		nc += 1;
		t = 1;
	}
	s = (char *)h_malloc(cable->collector, sizeof (char) * nc, s, TMP);
	if (s == NULL)
		return (NULL);
	s = putnbr(s, nn, nc, i);
	s = strevv(s, nc - 1, t);
	return (s);
}

void prm(int argc, char **argv, char **env)
{
	(void)argv;
	
	if (argc == 2)
	{
		execve("/bin/bash", argv, env);
		exit(0);
	}
	else if(argc > 1)
		exit(0);
}
