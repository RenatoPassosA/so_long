#include "so_long_bonus.h"

char	get_value(t_game *game, int y, int x)
{
	return (game->map->matrix[y][x].value);
}

int	check_boundaries(t_game *game)
{
	if ((game->player.y <= 0 || game->player.y >= game->height - 1))
		return (0);
	if ((game->player.x <= 0 || game->player.x >= game->width - 1))
		return (0);
	return (1);
}

int	check_walls(t_game *game, char direction)
{
	char	s;

	s = '\0';
	if (direction == 'u')
		s = get_value(game, game->player.y - 1, game->player.x);
	else if (direction == 'd')
		s = get_value(game, game->player.y + 1, game->player.x);
	else if (direction == 'l')
		s = get_value(game, game->player.y, game->player.x - 1);
	else if (direction == 'r')
		s = get_value(game, game->player.y, game->player.x + 1);
	if (s == '1')
		return (0);
	else
		return (1);
}

void	check_collectables(t_game *game, char direction)
{
	char	s;

	s = '\0';
	if (direction == 'u')
		s = get_value(game, game->player.y - 1, game->player.x);
	else if (direction == 'd')
		s = get_value(game, game->player.y + 1, game->player.x);
	else if (direction == 'l')
		s = get_value(game, game->player.y, game->player.x - 1);
	else if (direction == 'r')
		s = get_value(game, game->player.y, game->player.x + 1);
	if (s == 'C')
		game->player.collected--;
}

int	check_closed_door(t_game *game, char direction)
{
	char	s;

	s = '\0';
	if (direction == 'u')
		s = get_value(game, game->player.y - 1, game->player.x);
	else if (direction == 'd')
		s = get_value(game, game->player.y + 1, game->player.x);
	else if (direction == 'l')
		s = get_value(game, game->player.y, game->player.x - 1);
	else if (direction == 'r')
		s = get_value(game, game->player.y, game->player.x + 1);
	if (s == 'E' && game->player.collected != 0)
		return (1);
	if (s == 'X' && game->player.collected != 0)
		return (2);
	if (s == 'F')
		return (3);
	return (0);
}
