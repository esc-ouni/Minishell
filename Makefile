# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/03 17:40:51 by msamhaou          #+#    #+#              #
#    Updated: 2023/05/12 02:14:28 by msamhaou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
FLAGS = -w
AFLAGS = -lreadline
LINK = /Users/msamhaou/.brew/Cellar/readline/8.2.1/lib
INCLUDES = includes/
INC=/Users/msamhaou/.brew/Cellar/readline/8.2.1/include

ifeq ($(USER),idouni)
	LINK = /Users/idouni/.brew/opt/readline/lib
	INCLUDES = includes/
	INC=/Users/idouni/.brew/opt/readline/include/readline
endif

#		LIBFT
LIBFT_DIR = libft/
LIBFT_SRC	= libft/ft_atoi.c         libft/ft_isdigit.c      libft/ft_lstadd_front.c libft/ft_lstnew.c       libft/ft_memmove.c      libft/ft_putstr_fd.c      libft/ft_strncmp.c      libft/ft_tolower.c\
				libft/ft_bzero.c        libft/ft_islpha.c       libft/ft_lstclear.c     libft/ft_lstsize.c      libft/ft_memset.c       libft/ft_split.c        libft/ft_strlcat.c      libft/ft_strnstr.c      libft/ft_toupper.c\
				libft/ft_calloc.c       libft/ft_isprint.c      libft/ft_lstdelone.c    libft/ft_memchr.c       libft/ft_putchar_fd.c   libft/ft_strchr.c       libft/ft_strlcpy.c      libft/ft_strrchr.c\
				libft/ft_isalnum.c      libft/ft_itoa.c         libft/ft_lstiter.c      libft/ft_memcmp.c       libft/ft_putendl_fd.c   libft/ft_strdup.c       libft/ft_strlen.c       libft/ft_strtrim.c\
				libft/ft_isascii.c      libft/ft_lstadd_back.c  libft/ft_lstlast.c      libft/ft_memcpy.c       libft/ft_putnbr_fd.c    libft/ft_striteri.c     libft/ft_strmapi.c      libft/ft_substr.c
LIBFT_OBJ	=	$(LIBFT_SRC:.c=.o)

#		GNL
GNL_DIR = gnl/
GNL_SRC = gnl/get_next_line.c       gnl/get_next_line_utils.c
GNL_OBJ = $(GNL_SRC:.c=.o)

#		EXEC
EXEC_DIR = EXEC/
EXEC_SRC = EXEC/ft_built_in.c EXEC/ft_get_path.c EXEC/ft_env.c EXEC/ft_fork.c
EXEC_OBJ = $(EXEC_SRC:.c=.o)

#		PARS
PARS_DIR = PARS/
PARS_SRC = PARS/tools.c   PARS/tools_1.c PARS/tools_2.c PARS/ft_msplit.c   PARS/ft_mstrdup.c  PARS/ft_mstrjoin.c PARS/ft_mstrtrim.c PARS/ft_msubstr.c
PARS_OBJ = $(PARS_SRC:.c=.o)

MAIN_SRC = main.c
MAIN_OBJ = main.o


OBJ = $(LIBFT_OBJ) $(GNL_OBJ) $(EXEC_OBJ) $(PARS_OBJ) $(MAIN_OBJ)


NAME = minishell

all : $(NAME)
	@clear && echo "==Minishell_compiled=============="

$(NAME) : $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) -L $(LINK) -lreadline

%.o : %.c
	$(CC) $(FLAGS) -c $< -o $@ -I$(INCLUDES) -I$(INC)

clean :
	rm -rf $(OBJ)
fclean : clean
	rm -rf $(NAME)
re : clean all