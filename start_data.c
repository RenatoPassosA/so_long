/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:58:30 by rpassos-          #+#    #+#             */
/*   Updated: 2025/02/17 17:58:32 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	get_collectables(t_map_content *map_content)
{
	int	counter;

	counter = 0;
	while (map_content != NULL)
	{
		if (map_content->sqm == 'C')
			counter++;
		map_content = map_content->next;
	}
	return (counter);
}

t_image	new_sprite(void *mlx, char *path)
{
	t_image	sprite;

	sprite.xpm_ptr = mlx_xpm_file_to_image(mlx, path, &sprite.x, &sprite.y);
	if (sprite.xpm_ptr == NULL)
		mlx_destroy_image(mlx, sprite.xpm_ptr);
	sprite.x = TILE_SIZE;
	sprite.y = TILE_SIZE;
	return (sprite);
}

void	init_mlx(t_game *game, t_map *map)
{
	game->width = map->width;
	game->height = map->height;
	game->mlx_ptr = mlx_init();
	if (game->mlx_ptr == NULL)
		free(game->mlx_ptr);
	game->win_ptr = mlx_new_window(game->mlx_ptr, game->width * IMG_WIDTH,
			game->height * IMG_HEIGHT, "so_long");
	if (game->win_ptr == NULL)
		free(game->mlx_ptr);
}

void	start_data(t_game *game, t_map *map, t_map_content *map_content)
{
	void	*mlx;

	mlx = game->mlx_ptr;
	game->wall = new_sprite(mlx, "images/64wall.xpm");
	game->floor = new_sprite(mlx, "images/64grass.xpm");
	game->collectable = new_sprite(mlx, "images/64collectable.xpm");
	game->character_up = new_sprite(mlx, "images/64up.xpm");
	game->character_down = new_sprite(mlx, "images/64down.xpm");
	game->character_left = new_sprite(mlx, "images/64left.xpm");
	game->character_right = new_sprite(mlx, "images/64right.xpm");
	game->closed_door = new_sprite(mlx, "images/64closed_door.xpm");
	game->opened_door = new_sprite(mlx, "images/64opened_door.xpm");
	game->on_door = new_sprite(mlx, "images/64on_door.xpm");
	game->map = map;
	game->map_content = map_content;
	game->player.collected = get_collectables(map_content);
	game->player.moves = 0;
	game->player.direction = 'r';
}

char	get_value(t_game *game, int y, int x)
{
	return (game->map->matrix[y][x].value);
}
