#-lreadline
NAME = minishell
CC = gcc
FLAGS = -Wall -Wextra -Werror
LIBFT = libft/libft.a

all: $(NAME)

$(NAME): *.o $(LIBFT)
	$(CC) $(FLAGS) $(LIBFT) -o $(NAME) *.o -lreadline

*.o: *.c
	$(CC) $(FLAGS) -c *.c

$(LIBFT):
	@make -C ./libft

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all
