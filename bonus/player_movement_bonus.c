#include "so_long_bonus.h"

void	change_value(t_game *game, char direction, int closed_door)
{
	if (direction == 'u')
		game->player.y -= 1;
	else if (direction == 'd')
		game->player.y += 1;
	else if (direction == 'l')
		game->player.x -= 1;
	else if (direction == 'r')
		game->player.x += 1;
	if (closed_door == 3)
		finish_game(game);
}

void	set_new_values(t_game *game, char direction, int closed_door)
{
	int	prev_x;
	int	prev_y;
	int	x;
	int	y;

	prev_x = game->player.x;
	prev_y = game->player.y;
	x = -1;
	y = -1;
	change_value(game, direction, closed_door);
	if (closed_door == 2)
	{
		y = prev_y;
		x = prev_x;
	}
	if (game->map->matrix[prev_y][prev_x].value == 'X')
		game->map->matrix[prev_y][prev_x].value = 'E';
	else
		game->map->matrix[prev_y][prev_x].value = '0';
	if (closed_door == 1)
		game->map->matrix[game->player.y][game->player.x].value = 'X';
	else
		game->map->matrix[game->player.y][game->player.x].value = 'P';
	if (x != -1 && y != -1)
		game->map->matrix[y][x].value = 'E';
}

void	actions(t_game *game, char dir, int *check_movement)
{
	int	closed_door;

	closed_door = 0;
	if (!check_boundaries(game) || !check_walls(game, dir))
		return ;
	get_the_player(game);
	render_map(game);
	check_collectables(game, dir);
	closed_door = check_closed_door(game, dir);
	set_new_values(game, dir, closed_door);
	game->player.direction = dir;
	game->player.moves++;
	*check_movement = 1;
}

int	keyboard_action(int key, t_game *game)
{
	int	check_movement;

	check_movement = 0;
	if (game->end_game == 1)
	{
		put_str("Oh, you touched a enemy!");
		finish_game(game);
	}
	if (key == 65307)
		finish_game(game);
	else if (key == 119)
		actions(game, 'u', &check_movement);
	else if (key == 115)
		actions(game, 'd', &check_movement);
	else if (key == 97)
		actions(game, 'l', &check_movement);
	else if (key == 100)
		actions(game, 'r', &check_movement);
	if (check_movement)
	{
		check_surrounding(game);
		render_map(game);
	}
	return (0);
}
