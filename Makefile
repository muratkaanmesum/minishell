#-lreadline
NAME = so_long
CC = gcc
FLAGS = -Wall -Wextra -Werror
LIBFT = libft/libft.a
FT_PRINTF = ft_printf/libftprintf.a
FREAMS = -framework OpenGL -framework AppKit
MLX = ./minilibx/libmlx.a

all: $(NAME)

$(NAME): *.o $(MLX) $(LIBFT) $(FT_PRINTF)
	$(CC) $(FLAGS) $(LIBFT) $(FT_PRINTF) $(FREAMS) -o $(NAME) *.o $(MLX)

*.o: *.c
	$(CC) $(FLAGS) -c *.c gnl/*.c ft_printf/*.c

$(MLX):
	@make -C ./minilibx

$(LIBFT):
	@make -C ./libft

$(FT_PRINTF):
	@make -C ./ft_printf

clean:
	rm -f *.o
	@make clean -C ./minilibx

fclean: clean
	rm -f so_long
	
re: fclean all