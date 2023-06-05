# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: taha <taha@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/02 11:24:33 by msamhaou          #+#    #+#              #
#    Updated: 2023/06/04 19:12:07 by taha             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
FLAGS =
AFLAGS = -lreadline
LINK = /Users/msamhaou/.brew/Cellar/readline/8.2.1/lib
HEADERS = 	include/libft.h	include/minishell.h
INCLUDES = include
INC=/Users/msamhaou/.brew/Cellar/readline/8.2.1/include
HEADERS =	include/libft.h	include/minishell.h

OBJ_DIR = obj/

#********* LIBFT *************
LIBFT_DIR = libft/
LIBFT_SRC_FILES =	ft_atoi.c         ft_isascii.c      ft_itoa.c         ft_lstdelone.c    ft_lstsize.c      ft_memmove.c      ft_putnbr_fd.c    ft_strdup.c       ft_strlcpy.c      ft_strnstr.c      ft_tolower.c\
					ft_bzero.c        ft_isdigit.c      ft_lstadd_back.c  ft_lstiter.c      ft_memchr.c       ft_memset.c       ft_putstr_fd.c    ft_striteri.c     ft_strlen.c       ft_strrchr.c      ft_toupper.c\
					ft_calloc.c       ft_islpha.c       ft_lstadd_front.c ft_lstlast.c      ft_memcmp.c       ft_putchar_fd.c   ft_split.c        ft_strjoin.c      ft_strmapi.c      ft_strtrim.c      ft_soft_split.c\
					ft_isalnum.c      ft_isprint.c      ft_lstclear.c     ft_lstnew.c       ft_memcpy.c       ft_putendl_fd.c   ft_strchr.c       ft_strlcat.c      ft_strncmp.c      ft_substr.c
LIBFT_SRC = $(addprefix $(LIBFT_DIR), $(LIBFT_SRC_FILES))
LIBFT_OBJ_FILE = $(LIBFT_SRC_FILES:.c=.o)
LIBFT_OBJ = $(addprefix $(OBJ_DIR),$(LIBFT_OBJ_FILE))

#********* BUIL *************
# BUIL_DIR = BUILT/
# BUIL_SRC_FILES = ft_env_lst_tools.c  ft_exp_lst_tools.c  ft_export.c  ft_set_env.c  ft_set_exp.c  ft_unset.c
# BUIL_SRC = $(addprefix $(BUIL_DIR), $(BUIL_SRC_FILES))
# BUIL_OBJ_FILES = $(BUIL_SRC_FILES:.c=.o)
# BUIL_OBJ = $(addprefix $(OBJ_DIR), $(BUIL_OBJ_FILES))

#********* EXEC *************
EXEC_DIR = EXEC/
EXEC_SRC_FILES = ft_exec.c	ft_env_lst_tools.c  ft_exp_lst_tools.c  ft_export.c  ft_set_env.c  ft_set_exp.c  ft_unset.c
EXEC_SRC = $(addprefix $(EXEC_DIR), $(EXEC_SRC_FILES))
EXEC_OBJ_FILES = $(EXEC_SRC_FILES:.c=.o)
EXEC_OBJ = $(addprefix $(OBJ_DIR), $(EXEC_OBJ_FILES))

#********* MAIN *************
MAIN_SRC_FILE = main.c
MAIN_OBJ_FILE = main.o
MAIN_OBJ = $(addprefix $(OBJ_DIR), $(MAIN_OBJ_FILE))


INCLU = -I$(INCLUDES)
ALL_OBJ = $(LIBFT_OBJ) $(MAIN_OBJ) $(EXEC_OBJ)
NAME = minishell

all : $(NAME)

$(NAME) : $(OBJ_DIR) $(LIBFT_OBJ) $(EXEC_OBJ) $(MAIN_OBJ)
	$(CC) $(LIBFT_OBJ) $(EXEC_OBJ) $(MAIN_OBJ) -o $(NAME) $(INCLU)

$(OBJ_DIR) :
	mkdir -p $(OBJ_DIR)
$(OBJ_DIR)%.o : $(LIBFT_DIR)%.c
	$(CC) -c $< -o $@ $(INCLU)
$(OBJ_DIR)%.o : $(EXEC_DIR)%.c
	$(CC)  -c $< -o $@ $(INCLU)
$(MAIN_OBJ) : $(MAIN_SRC_FILE)
	$(CC) -c $< -o $@ $(INCLU)
clean :
	rm -rf $(OBJ_DIR)
fclean : clean
	rm -rf $(NAME)
re : clean all
