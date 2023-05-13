# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: idouni <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/12 14:32:47 by idouni            #+#    #+#              #
#    Updated: 2022/11/12 19:22:13 by idouni           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME   = libft.a

CC     = cc

RM     = rm -rf

FLAGS  = -Wall -Wextra -Werror

AR     = ar -rc

HR     = libft.h

PR     = ft_atoi.c \
	 ft_bzero.c \
	 ft_calloc.c \
	 ft_isalnum.c \
	 ft_isalpha.c \
	 ft_isascii.c \
	 ft_isdigit.c \
	 ft_isprint.c \
	 ft_itoa.c \
	 ft_memchr.c \
	 ft_memcmp.c \
	 ft_memcpy.c \
	 ft_memmove.c \
	 ft_memset.c \
	 ft_putchar_fd.c \
	 ft_putendl_fd.c \
	 ft_putnbr_fd.c \
	 ft_putstr_fd.c \
	 ft_split.c \
	 ft_strchr.c \
	 ft_strdup.c \
	 ft_striteri.c \
	 ft_strjoin.c \
	 ft_strlcat.c \
	 ft_strlcpy.c \
	 ft_strlen.c \
	 ft_strmapi.c \
	 ft_strncmp.c \
	 ft_strnstr.c \
	 ft_strrchr.c \
	 ft_strtrim.c \
	 ft_substr.c \
	 ft_tolower.c \
	 ft_toupper.c

PRB    = ft_lstadd_back.c \
	 ft_lstadd_front.c \
	 ft_lstclear.c \
	 ft_lstdelone.c \
	 ft_lstiter.c \
	 ft_lstlast.c \
	 ft_lstmap.c \
	 ft_lstnew.c \
	 ft_lstsize.c \

OBJ    = $(PR:%.c=%.o)

B_OBJ    = $(PRB:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ) $(HR)
	$(AR) $(NAME) $(OBJ)

bonus: $(B_OBJ) $(HR)
	$(AR) $(NAME) $(B_OBJ)

%.o: %.c $(HR)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(B_OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: all bonus clean fclean re
