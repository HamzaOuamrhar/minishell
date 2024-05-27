CC = cc  -Wall -Wextra -Werror -fsanitize=address
SRC = ft_split.c utils.c utils1.c utils2.c utils3.c utils4.c main.c libc1.c syntax.c set_env.c expander1.c parser.c quote_removal.c
OBJ = $(SRC:.c=.o)
NAME = ./minishell

all  : $(NAME)

$(NAME) : $(OBJ)
	$(CC) -lreadline $(OBJ) -o $(NAME)

%.o : %.c minishell.h
	$(CC) -c $< -o $@

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : clean
