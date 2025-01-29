#include "so_long_bonus.h"

void	update_monster_animation(t_game *game, char dir)
{
	if (dir == 'u' || dir == 'd')
	{
		game->animation.current_ud += 1;
		if (game->animation.current_ud == 2)
			game->animation.current_ud = 0;
	}
	else if (dir == 'l')
	{
		game->animation.current_l++;
		if (game->animation.current_l == 3)
			game->animation.current_l = 0;
	}
	else if (dir == 'r')
	{
		game->animation.current_r++;
		if (game->animation.current_r == 3)
			game->animation.current_r = 0;
	}
}

void	update_monster_collectable(t_game *game)
{
	char	tile;

	tile = game->map->matrix[game->monster.y][game->monster.x].value;
	if (tile == 'C')
		game->monster.on_collectable = 1;
	else if (tile == 'E')
		game->monster.on_collectable = 2;
	else if (tile == 'X')
		game->monster.on_collectable = 3;
	else if (tile == 'F')
		game->monster.on_collectable = 4;
	else
		game->monster.on_collectable = 0;
}

void	update_monster_coordinates(t_game *game, char dir)
{
	if (dir == 'u')
		game->monster.y -= 1;
	else if (dir == 'd')
		game->monster.y += 1;
	else if (dir == 'l')
		game->monster.x -= 1;
	else if (dir == 'r')
		game->monster.x += 1;
}

void	monster_move(t_game *game, char dir)
{
	if (!check_monster_boundaries(game) || !check_monster_walls(game, dir))
	{
		random_monster_move(game);
		return ;
	}
	if (game->monster.on_collectable == 1)
		game->map->matrix[game->monster.y][game->monster.x].value = 'C';
	else if (game->monster.on_collectable == 2)
		game->map->matrix[game->monster.y][game->monster.x].value = 'E';
	else if (game->monster.on_collectable == 3)
		game->map->matrix[game->monster.y][game->monster.x].value = 'X';
	else if (game->monster.on_collectable == 4)
		game->map->matrix[game->monster.y][game->monster.x].value = 'E';
	else
		game->map->matrix[game->monster.y][game->monster.x].value = '0';
	update_monster_coordinates(game, dir);
	update_monster_animation(game, dir);
	update_monster_collectable(game);
	game->map->matrix[game->monster.y][game->monster.x].value = 'M';
	render_map(game);
}

void	random_monster_move(t_game *game)
{
	char	random_dir;
	int		attempts;

	attempts = 0;
	while (attempts < 4)
	{
		random_dir = "udlr"[rand() % 4];
		if (check_monster_walls(game, random_dir)
			&& check_monster_boundaries(game))
		{
			monster_move(game, random_dir);
			return ;
		}
		attempts++;
	}
}
