# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: idouni <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/02 20:54:51 by idouni            #+#    #+#              #
#    Updated: 2023/04/02 20:54:57 by idouni           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LINK = /Users/idouni/.brew/opt/readline/lib
INCLUDES = includes/
INC=/Users/idouni/.brew/opt/readline/include/readline

NAME   = Minishell

CC     = cc

RM     = rm -rf

FLAGS  =  -Wall -Wextra -Werror #-fsanitize=address -g

HR     = Minishell.h

MND    = Minishell.c

TLS    = tools.c \
		tools_1.c \
		tools_2.c \
		G_N_L/get_next_line.c \
		G_N_L/get_next_line_utils.c \
		ft_msplit.c \
		ft_mstrdup.c \
		ft_mstrjoin.c \
		ft_mstrtrim.c \
		ft_msubstr.c

OBJ_M  = $(MND:%.c=%.o)

OBJ_T  = $(TLS:%.c=%.o)

all:
	gcc Minishell.c tools.c tools_1.c tools_2.c ft_msplit.c ft_mstrdup.c ft_mstrjoin.c ft_mstrtrim.c ft_msubstr.c libft.a -lreadline -L /Users/idouni/.brew/opt/readline/lib -o $(NAME)
	@clear && echo "==$(NAME)_compiled=============="
	./Minishell

# all: LIBFT $(NAME)

# LIBFT:
# 	@make -C LIBF

# $(NAME): $(OBJ_M) $(OBJ_T) $(HR)
# 	@$(CC) $(FLAGS) LIBF/libft.a $(OBJ_T) $(OBJ_M) -o $(NAME) -L $(LINK) -lreadline
# 	@clear && echo "==$(NAME)_compiled=============="
# 	./Minishell

# %.o: %.c $(HR)
# 	$(CC) $(FLAGS) -c $< -o $@ -I$(INCLUDES) -I$(INC)

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
