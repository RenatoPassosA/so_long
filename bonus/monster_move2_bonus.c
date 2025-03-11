/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster_move2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:27:53 by rpassos-          #+#    #+#             */
/*   Updated: 2025/01/30 14:27:55 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	check_monster_boundaries(t_game *game)
{
	if ((game->monster.y <= 0 || game->monster.y > game->height - 1))
		return (0);
	if ((game->monster.x <= 0 || game->monster.x > game->width - 1))
		return (0);
	return (1);
}

int	check_monster_walls(t_game *game, char direction)
{
	char	s;

	s = '\0';
	if (direction == 'u')
		s = get_value(game, game->monster.y - 1, game->monster.x);
	else if (direction == 'd')
		s = get_value(game, game->monster.y + 1, game->monster.x);
	else if (direction == 'l')
		s = get_value(game, game->monster.y, game->monster.x - 1);
	else if (direction == 'r')
		s = get_value(game, game->monster.y, game->monster.x + 1);
	if (s == '1')
		return (0);
	else
		return (1);
}

void	check_surrounding(t_game *game)
{
	if (get_value(game, game->monster.y + 1, game->monster.x) == 'P'
		|| get_value(game, game->monster.y - 1, game->monster.x) == 'P'
		|| get_value(game, game->monster.y, game->monster.x + 1) == 'P'
		|| get_value(game, game->monster.y, game->monster.x - 1) == 'P'
		|| get_value(game, game->monster.y + 1, game->monster.x + 1) == 'P'
		|| get_value(game, game->monster.y + 1, game->monster.x - 1) == 'P'
		|| get_value(game, game->monster.y - 1, game->monster.x + 1) == 'P'
		|| get_value(game, game->monster.y - 1, game->monster.x - 1) == 'P'
		|| get_value(game, game->monster.y, game->monster.x) == 'P')
		game->end_game = 1;
	if (get_value(game, game->monster.y, game->monster.x) == 'P'
		&& game->end_game == 1)
		game->map->matrix[game->monster.y][game->monster.x].value = 'M';
}

int	get_the_player(t_game *game)
{
	char	dir;

	dir = '\0';
	if (game->monster.x < game->player.x)
	{
		dir = 'r';
		game->monster.direction = 'r';
	}
	else if (game->monster.x > game->player.x)
	{
		dir = 'l';
		game->monster.direction = 'l';
	}
	else if (game->monster.y < game->player.y)
	{
		dir = 'd';
		game->monster.direction = 'd';
	}
	else if (game->monster.y > game->player.y)
	{
		dir = 'u';
		game->monster.direction = 'u';
	}
	monster_move(game, dir);
	return (0);
}
