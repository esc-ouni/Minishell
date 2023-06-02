# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/02 11:24:33 by msamhaou          #+#    #+#              #
#    Updated: 2023/06/02 15:39:25 by msamhaou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
FLAGS =
AFLAGS = -lreadline
LINK = /Users/msamhaou/.brew/Cellar/readline/8.2.1/lib
HEADERS = 	include/libft.h	include/minishell.h
INCLUDES = inlcude
INC=/Users/msamhaou/.brew/Cellar/readline/8.2.1/include
HEADERS =	includes/libft.h	includes/minishell.h

OBJ_DIR = obj/

LIBFT_DIR = libft/
LIBFT_SRC_FILES =	ft_atoi.c         ft_isascii.c      ft_itoa.c         ft_lstdelone.c    ft_lstsize.c      ft_memmove.c      ft_putnbr_fd.c    ft_strdup.c       ft_strlcpy.c      ft_strnstr.c      ft_tolower.c\
				ft_bzero.c        ft_isdigit.c      ft_lstadd_back.c  ft_lstiter.c      ft_memchr.c       ft_memset.c       ft_putstr_fd.c    ft_striteri.c     ft_strlen.c       ft_strrchr.c      ft_toupper.c\
				ft_calloc.c       ft_islpha.c       ft_lstadd_front.c ft_lstlast.c      ft_memcmp.c       ft_putchar_fd.c   ft_split.c        ft_strjoin.c      ft_strmapi.c      ft_strtrim.c\
				ft_isalnum.c      ft_isprint.c      ft_lstclear.c     ft_lstnew.c       ft_memcpy.c       ft_putendl_fd.c   ft_strchr.c       ft_strlcat.c      ft_strncmp.c      ft_substr.c
LIBFT_SRC = $(addprefix $(LIBFT_DIR), $(LIBFT_SRC_FILES))
LIBFT_OBJ_FILE = $(LIBFT_SRC_FILES:.c=.o)
LIBFT_OBJ = $(addprefix $(OBJ_DIR),$(LIBFT_OBJ_FILE))

EXEC_DIR = EXEC/
EXEC_SRC_FILES = ft_env_lst_tools.c ft_exp_lst_tools.c ft_set_env.c       ft_set_exp.c
EXEC_SRC = $(addprefix $(EXEC_DIR), $(EXEC_SRC_FILES))
EXEC_OBJ_FILES = $(EXEC_SRC_FILES:.c=.o)
EXEC_OBJ = $(addprefix $(OBJ_DIR), $(EXEC_OBJ_FILES))


MAIN_SRC_FILE = main.c
MAIN_OBJ_FILE = main.o
MAIN_OBJ = $(addprefix $(OBJ_DIR), $(MAIN_OBJ_FILE))

INCLU = -I $(INCLUDES)


ALL_OBJ = $(LIBFT_OBJ) $(EXEC_OBJ) $(MAIN_OBJ)
NAME = minishell

all : $(NAME)

$(NAME) : $(OBJ_DIR) $(ALL_OBJ)
	$(CC) $(FLAGS) $(ALL_OBJ) -lreadline -L $(LINK) -o $(NAME)

$(OBJ_DIR) :
	mkdir -p $(OBJ_DIR)
$(LIBFT_OBJ) : $(LIBFT_SRC)
	$(CC) $(FLAGS) -c $< -o $@ $(INCLU)
$(EXEC_OBJ) : $(EXEC_SRC)
	$(CC) $(FLAGS) -c $< -o $@ $(INCLU)
$(MAIN_OBJ) : $(MAIN_SRC_FILE)
	$(CC) $(FLAGS) -c $< -o $@ $(INCLU)
clean :
	rm -rf $(OBJ_DIR)
fclean : clean
	rm -rf $(NAME)
re : clean all
