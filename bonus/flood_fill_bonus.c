/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:27:41 by rpassos-          #+#    #+#             */
/*   Updated: 2025/01/30 14:27:42 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static int	collectables_counter(t_map_content *content)
{
	int	collect_counter;

	collect_counter = 0;
	while (content->next != NULL)
	{
		if (content->sqm == 'C')
			collect_counter++;
		content = content->next;
	}
	return (collect_counter);
}

static int	*get_position(t_map *map, char value)
{
	int	*coordinates;
	int	x;
	int	y;

	x = 0;
	y = 0;
	coordinates = (int *)malloc(sizeof(int) * 2);
	if (!coordinates)
		return (NULL);
	while (y < map->height)
	{
		while (x < map->width)
		{
			if (map->matrix[y][x].value == value)
			{
				coordinates[0] = y;
				coordinates[1] = x;
				return (coordinates);
			}
			x++;
		}
		x = 0;
		y++;
	}
	return (NULL);
}

static void	flood_fill(t_map *map, int y, int x)
{
	if (x < 0 || y < 0 || x >= map->width || y >= map->height)
		return ;
	if (map->matrix[y][x].value == '1' || map->matrix[y][x].visited == 1)
		return ;
	if (map->matrix[y][x].value == 'C')
		map->collectable_counter++;
	if (map->matrix[y][x].value == 'E')
		map->found_exit = 1;
	if (map->matrix[y][x].value != 'P')
		map->matrix[y][x].visited = 1;
	flood_fill(map, y, x + 1);
	flood_fill(map, y, x - 1);
	flood_fill(map, y + 1, x);
	flood_fill(map, y - 1, x);
}

void	run_flood_fill(t_map *map, t_map_content *map_content, t_game *game)
{
	int	*starter_position;
	int	y;
	int	x;
	int	colletables_in_map;

	starter_position = get_position(map, 'P');
	game->player.y = starter_position[0];
	game->player.x = starter_position[1];
	y = starter_position[0];
	x = starter_position[1];
	free(starter_position);
	starter_position = get_position(map, 'M');
	game->monster.y = starter_position[0];
	game->monster.x = starter_position[1];
	y = starter_position[0];
	x = starter_position[1];
	free(starter_position);
	map->collectable_counter = 0;
	map->found_exit = 0;
	flood_fill(map, y, x);
	colletables_in_map = collectables_counter(map_content);
	if (map->collectable_counter != colletables_in_map || map->found_exit != 1)
		clear_data(map, map_content, game, 9);
}
