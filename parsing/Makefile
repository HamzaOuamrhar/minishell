CC = cc  -Wall -Wextra -Werror
SRC = ft_split.c ft_strdup.c utils.c utils1.c utils2.c main.c
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
