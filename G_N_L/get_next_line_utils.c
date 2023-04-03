/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 17:13:26 by idouni            #+#    #+#             */
/*   Updated: 2022/11/28 14:42:57 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_gstrlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_gstrjoin(char *s1, char *s2)
{
	int		i;
	int		i2;
	char	*new;

	i = 0;
	i2 = 0;
	if (!s1)
	{
		s1 = malloc(sizeof(char) * 1);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	new = malloc(sizeof(char) * (ft_gstrlen(s1) + ft_gstrlen(s2) + 1));
	if (!new)
		return (NULL);
	while (s1[i])
		new[i++] = s1[i2++];
	i = 0;
	while (s2[i])
		new[i2++] = s2[i++];
	new[i2] = '\0';
	free (s1);
	return (new);
}

int	gcheck(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*str_alloc(int fd, char	*buffer)
{
	int		bytes;
	char	*buff;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	bytes = 1;
	while (!gcheck(buffer) && bytes != 0)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buffer);
			free (buff);
			return (NULL);
		}
		buff[bytes] = '\0';
		buffer = ft_gstrjoin(buffer, buff);
	}
	free (buff);
	return (buffer);
}

char	*r_reset(char *buffer)
{
	int		i;
	int		i2;
	char	*new;

	i = 0;
	if (!buffer)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	new = malloc(sizeof(char) * (ft_gstrlen(buffer) - i + 1));
	if (!new)
		return (NULL);
	i2 = i + 1;
	i = 0;
	while (buffer[i2])
		new[i++] = buffer[i2++];
	new[i] = '\0';
	free(buffer);
	return (new);
}
