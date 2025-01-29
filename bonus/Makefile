NAME = so_long
CC = cc
CCFLAGS = -Wall -Wextra -Werror -Imlx
SRC = so_long_bonus.o parse_map_bonus.o parse_map_utils_bonus.o start_data_bonus.o render_map_bonus.o player_movement_bonus.o monster_move_bonus.o monster_move2_bonus.o finish_game_bonus.o error_handling_bonus.o error_handling2_bonus.o check_for_movements_bonus.o get_next_line_bonus.o get_next_line_utils_bonus.o flood_fill_bonus.o
MLX = ../mlx/libmlx.a -L/usr/lib -lXext -lX11

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
