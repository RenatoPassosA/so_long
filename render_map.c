/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:26:27 by rpassos-          #+#    #+#             */
/*   Updated: 2025/01/30 14:29:53 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	return (0);
}
