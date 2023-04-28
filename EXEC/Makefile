CC=cc
CFLAGS= -Wall -Wextra -Werror
FLAGS= -lreadline

LINK=/Users/$(USER)/.brew/Cellar/readline/8.2.1/lib
INC=/Users/$(USER)/.brew/Cellar/readline/8.2.1/include
SRC=main.c	ft_built_in.c	ft_get_path.c
LIBFT=libft/libft.a
OBJ=$(SRC:%.c=%.o)

NAME=minishell
all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(FLAGS) -L$(LINK) -I$(INC) 

%.o:%.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INC)

.PHONY: all clean