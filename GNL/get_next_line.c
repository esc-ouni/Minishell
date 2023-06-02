/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 00:47:53 by msamhaou          #+#    #+#             */
/*   Updated: 2022/11/25 15:49:00 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_read(char *str, int fd)
{
	char	*buff;
	int		rdb;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	rdb = 1;
	while (rdb > 0 && !ft_isnewline(str))
	{
		rdb = read(fd, buff, BUFFER_SIZE);
		if (rdb < 0)
			return (free(str), free(buff), NULL);
		buff[rdb] = '\0';
		str = ft_strjoin(str, buff);
		if (!str)
			return (free(buff), NULL);
		if (!rdb && str[0] == '\0')
			return (free(buff), free(str), NULL);
	}
	return (free(buff), str);
}

static char	*ft_line(char *str)
{
	size_t		i;
	char		*line;

	i = ft_linelen(str);
	line = malloc(i + 2);
	if (!line)
		return (free(str), NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*ft_next(char *str)
{
	char	*next;
	size_t	len;
	size_t	j;

	len = ft_linelen(str);
	if (!str[len])
	{
		free (str);
		return (NULL);
	}
	next = (char *)malloc((ft_strlen(str) - len + 1) * sizeof(char));
	if (!next)
		return (free(str), NULL);
	len++;
	j = 0;
	while (str[len])
	{
		next[j] = str[len];
		len++;
		j++;
	}
	next[j] = '\0';
	free(str);
	return (next);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = ft_read(str, fd);
	if (!str)
		return (NULL);
	line = ft_line(str);
	str = ft_next(str);
	return (line);
}
