NAME = so_long
NAME_BONUS = so_long_bonus
CC = cc
CCFLAGS = -Wall -Wextra -Werror -Imlx
SRC = so_long.o parse_map.o utils.o start_data.o render_map.o player_movement.o finish_game.o error_handling.o error_handling2.o check_for_movement.o get_next_line.o get_next_line_utils.o flood_fill.o
SRC_BONUS = bonus/start_data_bonus.o bonus/so_long_bonus.o bonus/render_map_bonus.o bonus/player_movement_bonus.o bonus/parse_map_utils_bonus.o bonus/parse_map_bonus.o bonus/monster_move2_bonus.o bonus/monster_move_bonus.o bonus/get_next_line_utils_bonus.o bonus/get_next_line_bonus.o bonus/flood_fill_bonus.o bonus/finish_game_bonus.o bonus/error_handling2_bonus.o bonus/error_handling_bonus.o bonus/check_for_movements_bonus.o
OBJS_BONUS := $(SRC_BONUS:%.c=%.o)
MLX = mlx/libmlx.a -L/usr/lib -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CCFLAGS) -o $(NAME) $(SRC) $(MLX)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS)
	$(CC) $(CCFLAGS) -o $(NAME_BONUS) $(OBJS_BONUS) $(MLX)
.o:.c
	$(CC) $(CCFLAGS) -c $< -o $@ 

clean:
	rm -f $(SRC) $(SRC_BONUS)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

re: clean all

.PHONY: all bonus clean fclean
