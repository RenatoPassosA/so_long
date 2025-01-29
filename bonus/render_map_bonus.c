#include "so_long_bonus.h"

void	render_player_direction(t_game *game, int line, int column)
{
	if (game->player.direction == 'u')
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->character_up.xpm_ptr, column * TILE_SIZE, line * TILE_SIZE);
	if (game->player.direction == 'd')
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->character_down.xpm_ptr, column * TILE_SIZE, line * TILE_SIZE);
	if (game->player.direction == 'l')
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->character_left.xpm_ptr, column * TILE_SIZE, line * TILE_SIZE);
	if (game->player.direction == 'r')
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->character_right.xpm_ptr, column * TILE_SIZE, line
			* TILE_SIZE);
}

void	render_monster_direction(t_game *game, int line, int column)
{
	int	current_frame;

	if (game->monster.direction == 'u' || game->monster.direction == 'd')
	{
		current_frame = game->animation.current_ud;
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->animation.walk_ud[current_frame].xpm_ptr, column * TILE_SIZE,
			line * TILE_SIZE);
	}
	if (game->monster.direction == 'l')
	{
		current_frame = game->animation.current_l;
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->animation.walk_left[current_frame].xpm_ptr, column
			* TILE_SIZE, line * TILE_SIZE);
	}
	if (game->monster.direction == 'r')
	{
		current_frame = game->animation.current_r;
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->animation.walk_right[current_frame].xpm_ptr, column
			* TILE_SIZE, line * TILE_SIZE);
	}
}

void	render_sprite(t_game *game, t_image sprite, int line, int column)
{
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, sprite.xpm_ptr, column
		* TILE_SIZE, line * TILE_SIZE);
}

void	check_sprite(t_game *game, int y, int x)
{
	char	value;

	value = game->map->matrix[y][x].value;
	if (value == '0')
		render_sprite(game, game->floor, y, x);
	else if (value == '1')
		render_sprite(game, game->wall, y, x);
	else if (value == 'P')
		render_player_direction(game, y, x);
	else if (value == 'C')
		render_sprite(game, game->collectable, y, x);
	else if (value == 'M')
		render_monster_direction(game, y, x);
	else if (value == 'E')
	{
		if (game->player.collected == 0)
		{
			render_sprite(game, game->opened_door, y, x);
			game->map->matrix[y][x].value = 'F';
		}
		else
			render_sprite(game, game->closed_door, y, x);
	}
	else if (value == 'X')
		render_sprite(game, game->on_door, y, x);
}

int	render_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			check_sprite(game, y, x);
			x++;
		}
		y++;
	}
	show_movements(game);
	return (0);
}
