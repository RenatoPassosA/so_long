/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:27:27 by rpassos-          #+#    #+#             */
/*   Updated: 2025/01/30 14:27:29 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static int	map_counter(t_map_content *map_content, t_game *game)
{
	game->count_p = 0;
	game->count_e = 0;
	game->count_c = 0;
	game->count_m = 0;
	while (map_content != NULL)
	{
		if (map_content->sqm == 'P')
			game->count_p++;
		if (map_content->sqm == 'E')
			game->count_e++;
		if (map_content->sqm == 'C')
			game->count_c++;
		if (map_content->sqm == 'M')
			game->count_m++;
		map_content = map_content->next;
	}
	if (game->count_p != 1 || game->count_e != 1)
		return (3);
	if (game->count_c == 0)
		return (5);
	if (game->count_m != 1)
		return (11);
	return (0);
}

static int	check_borders(t_map *map)
{
	int	y;
	int	index;

	y = 0;
	index = 0;
	while (y < map->height)
	{
		if (map->matrix[y][0].value != '1' || map->matrix[y][map->width
			- 1].value != '1')
			return (6);
		y++;
	}
	while (index < map->width)
	{
		if (map->matrix[0][index].value != '1')
			return (7);
		if (map->matrix[map->height - 1][index].value != '1')
			return (8);
		index++;
	}
	return (0);
}

void	clear_data(t_map *map, t_map_content *map_content, t_game *game, int n)
{
	get_next_line(1000);
	if (n != 10)
		free_matrix(map->matrix, map->height);
	error_msgs(n);
	ft_lstclear(&map_content);
	free(map_content);
	free(map);
	free(game);
	exit(0);
}

static int	check_values(t_map_content *map_content)
{
	while (map_content->next != NULL)
	{
		if (map_content->sqm != '0' && map_content->sqm != '1'
			&& map_content->sqm != 'P' && map_content->sqm != 'C'
			&& map_content->sqm != 'E' && map_content->sqm != 'M')
			return (12);
		map_content = map_content->next;
	}
	return (0);
}

void	error_handling(t_map *map, t_map_content *map_content, t_game *game)
{
	int	n;

	n = map_size(map);
	if (n != 0)
		clear_data(map, map_content, game, n);
	n = map_counter(map_content, game);
	if (n != 0)
		clear_data(map, map_content, game, n);
	n = check_borders(map);
	if (n != 0)
		clear_data(map, map_content, game, n);
	n = check_values(map_content);
	if (n != 0)
		clear_data(map, map_content, game, n);
}
