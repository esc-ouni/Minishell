# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/02 11:24:33 by msamhaou          #+#    #+#              #
#    Updated: 2023/06/03 12:21:06 by msamhaou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
INCLUDES = include

OBJ_DIR = obj/

#********* LIBFT *************
LIBFT_DIR = libft/
LIBFT_SRC_FILES =	ft_isnum.c
LIBFT_SRC = $(addprefix $(LIBFT_DIR), $(LIBFT_SRC_FILES))
LIBFT_OBJ_FILE = $(LIBFT_SRC_FILES:.c=.o)
LIBFT_OBJ = $(addprefix $(OBJ_DIR),$(LIBFT_OBJ_FILE))

#********* EXEC *************
EXEC_DIR = EXEC/
EXEC_SRC_FILES = ft_exemple.c
EXEC_SRC = $(addprefix $(EXEC_DIR), $(EXEC_SRC_FILES))
EXEC_OBJ_FILES = $(EXEC_SRC_FILES:.c=.o)
EXEC_OBJ = $(addprefix $(OBJ_DIR), $(EXEC_OBJ_FILES))

#********* MAIN *************
MAIN_SRC_FILE = main.c
MAIN_OBJ_FILE = main.o
MAIN_OBJ = $(addprefix $(OBJ_DIR), $(MAIN_OBJ_FILE))


ALL_OBJ =  $(LIBFT_OBJ) $(MAIN_OBJ) $(EXEC_OBJ)
NAME = minishell

all : $(NAME)

$(NAME) : $(OBJ_DIR) $(ALL_OBJ)
	$(CC) $(ALL_OBJ) -o $(NAME)

$(OBJ_DIR) :
	mkdir -p $(OBJ_DIR)
$(LIBFT_OBJ) : $(LIBFT_SRC)
	$(CC) -c $< -o $@ -I$(INCLUDES)
$(EXEC_OBJ) : $(EXEC_SRC)
	$(CC) -c $< -o $@ -I$(INCLUDES)
$(MAIN_OBJ) : $(MAIN_SRC_FILE)
	$(CC) -c $< -o $@ -I$(INCLUDES)
clean :
	rm -rf $(OBJ_DIR)
fclean : clean
	rm -rf $(NAME)
re : clean all
