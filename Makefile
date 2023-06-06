# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/02 11:24:33 by msamhaou          #+#    #+#              #
#    Updated: 2023/06/06 15:45:30 by msamhaou         ###   ########.fr        #
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

ifeq ($(USER),idouni)
	LINK = /Users/idouni/.brew/Cellar/readline/8.2.1/lib
	HEADERS = 	include/libft.h	include/minishell.h
	INCLUDES = include
	INC=/Users/idouni/.brew/Cellar/readline/8.2.1/include
	HEADERS =	include/libft.h	include/minishell.h
endif

OBJ_DIR = obj/

#********* LIBFT *************
LIBFT_DIR = libft/
LIBFT_SRC_FILES =	ft_atoi.c         ft_isascii.c      ft_itoa.c         ft_lstdelone.c    ft_lstsize.c      ft_memmove.c      ft_putnbr_fd.c    ft_strdup.c       ft_strlcpy.c      ft_strnstr.c      ft_tolower.c\
					ft_bzero.c        ft_isdigit.c      ft_lstadd_back.c  ft_lstiter.c      ft_memchr.c       ft_memset.c       ft_putstr_fd.c    ft_striteri.c     ft_strlen.c       ft_strrchr.c      ft_toupper.c\
					ft_calloc.c       ft_islpha.c       ft_lstadd_front.c ft_lstlast.c      ft_memcmp.c       ft_putchar_fd.c   ft_split.c        ft_strmapi.c      ft_strtrim.c      ft_soft_split.c\
					ft_isalnum.c      ft_isprint.c      ft_lstclear.c     ft_lstnew.c       ft_memcpy.c       ft_putendl_fd.c   ft_strchr.c       ft_strlcat.c      ft_strncmp.c      ft_substr.c       ft_trim_len.c
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
EXEC_SRC_FILES =	ft_builtin.c       ft_exp_lst_tools.c ft_free.c          ft_set_env.c       ft_unset.c\
					ft_child.c         ft_export.c        ft_heredoc.c       ft_set_exp.c\
					ft_env_lst_tools.c ft_export_env.c    ft_lst_finder.c    ft_skip_char.c\
					ft_exec.c          ft_export_exp.c    ft_msoft_split.c   ft_test_tools.c
EXEC_SRC = $(addprefix $(EXEC_DIR), $(EXEC_SRC_FILES))
EXEC_OBJ_FILES = $(EXEC_SRC_FILES:.c=.o)
EXEC_OBJ = $(addprefix $(OBJ_DIR), $(EXEC_OBJ_FILES))

#********* PARS *************
PARS_DIR = PARS/
PARS_SRC_FILES =	expander.c printer.c lexer.c memory.c parser.c syntax.c tools_1.c tools_10.c tools_11.c tools_12.c tools_13.c\
					tools_2.c tools_3.c tools_4.c tools_5.c tools_6.c tools_7.c tools_8.c tools_9.c
PARS_SRC = $(addprefix $(PARS_DIR), $(PARS_SRC_FILES))
PARS_OBJ_FILES = $(PARS_SRC_FILES:.c=.o)
PARS_OBJ = $(addprefix $(OBJ_DIR), $(PARS_OBJ_FILES))

#********* GNL **************
GNL_DIR = GNL/
GNL_SRC_FILES =	get_next_line.c       get_next_line_utils.c
GNL_SRC = $(addprefix $(GNL_DIR), $(GNL_SRC_FILES))
GNL_OBJ_FILES = $(GNL_SRC_FILES:.c=.o)
GNL_OBJ = $(addprefix $(OBJ_DIR), $(GNL_OBJ_FILES))

#********* MAIN *************
MAIN_SRC_FILE = main.c
MAIN_OBJ_FILE = main.o
MAIN_OBJ = $(addprefix $(OBJ_DIR), $(MAIN_OBJ_FILE))


INCLU = -I$(INCLUDES) -I$(INC)
ALL_OBJ = $(LIBFT_OBJ) $(GNL_OBJ) $(MAIN_OBJ) $(EXEC_OBJ) $(PARS_OBJ)
NAME = minishell

all : $(NAME)

$(NAME) : $(OBJ_DIR) $(ALL_OBJ)
	$(CC) -lreadline $(ALL_OBJ) -o $(NAME) -L$(LINK)

$(OBJ_DIR) :
	mkdir -p $(OBJ_DIR)
$(OBJ_DIR)%.o : $(LIBFT_DIR)%.c
	$(CC) -c $< -o $@ $(INCLU)
$(OBJ_DIR)%.o : $(EXEC_DIR)%.c
	$(CC)  -c $< -o $@ $(INCLU)
$(OBJ_DIR)%.o : $(PARS_DIR)%.c
	$(CC)  -c $< -o $@ $(INCLU)
$(OBJ_DIR)%.o : $(GNL_DIR)%.c
	$(CC)  -c $< -o $@ $(INCLU)
$(MAIN_OBJ) : $(MAIN_SRC_FILE)
	$(CC) -c $< -o $@ $(INCLU)
clean :
	rm -rf $(OBJ_DIR)
fclean : clean
	rm -rf $(NAME)
re : clean all
