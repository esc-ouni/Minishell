/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 10:33:15 by idouni            #+#    #+#             */
/*   Updated: 2022/11/27 17:23:16 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*str_alloc(int fd, char	*str);
char	*r_reset(char *buff);
int		gcheck(char *buff);
int		ft_gstrlen(char *s);
char	*ft_gstrjoin(char *s1, char *s2);
char	*line_extract(char *str);

#endif
