/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_data_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:28:36 by rpassos-          #+#    #+#             */
/*   Updated: 2025/01/30 14:28:37 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static int	get_amount(t_map_content *map_content, char search)
{
	int	counter;

	counter = 0;
	while (map_content != NULL)
	{
		if (map_content->sqm == search)
			counter++;
		map_content = map_content->next;
	}
	return (counter);
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

static t_image	new_sprite(void *mlx, char *path)
{
	t_image	sprite;

	sprite.xpm_ptr = mlx_xpm_file_to_image(mlx, path, &sprite.x, &sprite.y);
	if (sprite.xpm_ptr == NULL)
		mlx_destroy_image(mlx, sprite.xpm_ptr);
	sprite.x = TILE_SIZE;
	sprite.y = TILE_SIZE;
	return (sprite);
}

static void	start_animation_data(t_game *game)
{
	void	*mlx;

	mlx = game->mlx_ptr;
	game->animation.walk_left = (t_image *)malloc(sizeof(t_image) * 3);
	game->animation.walk_right = (t_image *)malloc(sizeof(t_image) * 3);
	game->animation.walk_ud = (t_image *)malloc(sizeof(t_image) * 2);
	if (!game->animation.walk_right || !game->animation.walk_left
		|| !game->animation.walk_ud)
		return ;
	game->animation.walk_left[0] = new_sprite(mlx, "images/64ewalkl1.xpm");
	game->animation.walk_left[1] = new_sprite(mlx, "images/64ewalkl2.xpm");
	game->animation.walk_left[2] = new_sprite(mlx, "images/64ewalkl3.xpm");
	game->animation.current_l = 0;
	game->animation.walk_right[0] = new_sprite(mlx, "images/64ewalkr1.xpm");
	game->animation.walk_right[1] = new_sprite(mlx, "images/64ewalkr2.xpm");
	game->animation.walk_right[2] = new_sprite(mlx, "images/64ewalkr3.xpm");
	game->animation.current_r = 0;
	game->animation.walk_ud[0] = new_sprite(mlx, "images/64ud1.xpm");
	game->animation.walk_ud[1] = new_sprite(mlx, "images/64ud3.xpm");
	game->animation.current_ud = 0;
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
	game->player.collected = get_amount(map_content, 'C');
	game->num_monsters = get_amount(map_content, 'M');
	game->player.moves = 0;
	game->player.direction = 'r';
	game->monster.direction = 'l';
	game->monster.move_check = 1;
	game->monster.on_collectable = 0;
	game->end_game = 0;
	start_animation_data(game);
}
