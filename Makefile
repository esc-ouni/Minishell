# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: idouni <idouni@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/03 17:40:51 by msamhaou          #+#    #+#              #
#    Updated: 2023/05/31 12:42:28 by idouni           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



CC = cc
FLAGS =
AFLAGS = -lreadline
LINK = /Users/msamhaou/.brew/Cellar/readline/8.2.1/lib
HEADERS = includes/get_next_line.h	includes/libft.h	includes/minishell.h
INCLUDES = includes/
INC=/Users/msamhaou/.brew/Cellar/readline/8.2.1/include

ifeq ($(USER),idouni)
	LINK = /Users/idouni/.brew/Cellar/readline/8.2.1/lib
	HEADERS = includes/get_next_line.h	includes/libft.h	includes/minishell.h
	INCLUDES = includes/
	INC=/Users/idouni/.brew/Cellar/readline/8.2.1/include
endif

#		LIBFT
LIBFT_DIR = libft/
LIBFT_SRC	=	libft/ft_atoi.c         libft/ft_isdigit.c      libft/ft_lstadd_front.c libft/ft_lstnew.c       libft/ft_memmove.c      libft/ft_putstr_fd.c      libft/ft_strncmp.c      libft/ft_tolower.c\
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
EXEC_SRC =	EXEC/export_tool.c      EXEC/ft_built_in.c      EXEC/ft_env.c           EXEC/ft_env_tools.c\
			EXEC/ft_export_plus.c   EXEC/ft_free.c          EXEC/ft_heredoc.c       EXEC/ft_init.c          EXEC/ft_unset.c\
			EXEC/export_tool_plus.c EXEC/ft_built_in_plus.c EXEC/ft_env_plus.c      EXEC/ft_export.c\
			EXEC/ft_fork.c          EXEC/ft_get_path.c      EXEC/ft_in_out_files.c  EXEC/ft_sort_env.c
EXEC_OBJ = $(EXEC_SRC:.c=.o)

#		PARS
PARS_DIR = PARS/
PARS_SRC = PARS/expander.c PARS/lexer.c PARS/memory.c PARS/parser.c PARS/syntax.c PARS/tools_1.c PARS/tools_2.c PARS/tools_3.c PARS/tools_4.c PARS/tools_5.c PARS/tools_6.c PARS/tools_7.c PARS/tools_8.c PARS/tools_9.c PARS/tools_10.c PARS/tools_11.c PARS/printer.c
PARS_OBJ = $(PARS_SRC:.c=.o)

MAIN_SRC = main.c
MAIN_OBJ = main.o


OBJ = $(LIBFT_OBJ) $(GNL_OBJ) $(EXEC_OBJ) $(PARS_OBJ) $(MAIN_OBJ)


NAME = minishell

all : $(NAME)


$(NAME) : $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -lreadline -L $(LINK) -o $(NAME)

%.o : %.c $(HEADERS)
	$(CC) $(FLAGS) -c $< -o $@ -I$(INCLUDES) -I$(INC)

clean :
	rm -rf $(OBJ)
fclean : clean
	rm -rf $(NAME)
re : clean all
