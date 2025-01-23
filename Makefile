NAME = so_long
CC = gcc
CCFLAGS = -Wall -Wextra -Werror -Imlx
SRC = so_long.o parse_map.o get_next_line.o get_next_line_utils.o utils.o error_handling.o flood_fill.o
MLX = mlx/libmlx.a -L/usr/lib -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CCFLAGS) -o $(NAME) $(SRC) $(MLX)

.o:.c
	$(CC) $(CCFLAGS) -c $< -o $@ 

compile:
	cc -Wall -Wextra -Werror -Imlx -o so_long *.c mlx/libmlx.a -L/usr/lib -lXext -lX11 -lm -g

clean:
	rm -f $(SRC)

fclean: clean
	rm -f $(NAME)

re: clean all

.PHONY: all bonus clean fclean
