# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: idouni <idouni@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/02 20:54:51 by idouni            #+#    #+#              #
#    Updated: 2023/05/22 17:23:12 by idouni           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LINK = /Users/idouni/.brew/opt/readline/lib
INCLUDES = includes/
INC=/Users/idouni/.brew/opt/readline/include/readline

NAME   = Minishell

CC     = cc

RM     = rm -rf

FLAGS  =  -Wall -Wextra -Werror

HR     = Minishell.h

MND    = Minishell.c

TLS    = expander.c \
		lexer.c \
		memory.c \
		parser.c \
		printer.c \
		syntax.c \
		tools_1.c \
		tools_2.c \
		tools_3.c \
		tools_4.c \
		tools_5.c \
		tools_6.c \
		tools_7.c \
		tools_8.c \
		tools_9.c \


OBJ_M  = $(MND:%.c=%.o)

OBJ_T  = $(TLS:%.c=%.o)

# all:
# 	gcc Minishell.c ft_msplit.c ft_mstrdup.c ft_mstrtrim.c memory.c printer.c syntax.c tools.c tools_2.c libft.a -lreadline -L /Users/idouni/.brew/opt/readline/lib -o $(NAME)
# 	@clear && echo "==$(NAME)_compiled=============="
# 	./Minishell

all: LIBFT $(NAME)

LIBFT:
	@make -C LIBF

$(NAME): $(OBJ_M) $(OBJ_T) $(HR)
	@$(CC) $(FLAGS) LIBF/libft.a $(OBJ_T) $(OBJ_M) -o $(NAME) -L $(LINK) -lreadline
	@clear && echo "==$(NAME)_compiled=============="
	./Minishell

%.o: %.c $(HR)
	$(CC) $(FLAGS) -c $< -o $@ -I$(INCLUDES) -I$(INC)

clean:
	@make clean -C LIBF
	$(RM) $(OBJ_M)
	$(RM) $(OBJ_T)
	@clear && echo "==Object_files_deleted=========="

fclean: clean
	@make fclean -C LIBF
	$(RM) $(NAME)
	@clear && echo "==All_created_files_deleted====="

re: fclean all
	@clear && echo "==Compilation_reseted==========="

.PHONY: all clean fclean re LIBFT
