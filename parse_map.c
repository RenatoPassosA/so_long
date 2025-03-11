/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:58:23 by rpassos-          #+#    #+#             */
/*   Updated: 2025/02/17 17:58:24 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_map_content	*parse_line(char *line, t_map_content *map_content)
{
	int				index;
	t_map_content	*current;
	t_map_content	*new_node;

	index = 0;
	if (!map_content)
	{
		map_content = lst_new(line[index]);
		index++;
	}
	current = map_content;
	while (current->next != NULL)
		current = current->next;
	while (line[index] != '\0')
	{
		new_node = lst_new(line[index]);
		current->next = new_node;
		current = current->next;
		index++;
		if (line[index] == '\n')
			index++;
	}
	return (map_content);
}

static void	check_x_len(char *line, t_game *game, t_map *map,
		t_map_content *map_content)
{
	size_t	len;

	len = ft_strlen(line);
	if (line[len - 1] == '\n')
		len--;
	if (game->x_axis == 0)
		game->x_axis = len;
	else if (game->x_axis != (int)len)
	{
		free(line);
		clear_data(map, map_content, game, 10);
	}
}

void	free_matrix(t_values **matrix, int y)
{
	int	i;

	i = 0;
	while (i <= y)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	fill_matrix(t_map_content *map_content, t_map *map)
{
	int	x;
	int	y;

	x = 0;
	y = -1;
	map->matrix = (t_values **)malloc(sizeof(t_values *) * map->height);
	if (!map->matrix)
		return ;
	while (++y < map->height)
	{
		map->matrix[y] = (t_values *)malloc(sizeof(t_values) * map->width);
		if (!map->matrix[y])
		{
			free_matrix(map->matrix, y);
			return ;
		}
		while (x < map->width)
		{
			map->matrix[y][x].value = map_content->sqm;
			map->matrix[y][x].visited = 0;
			map_content = map_content->next;
			x++;
		}
		x = 0;
	}
}

t_map_content	*read_map(char *file, t_map *map, t_map_content *map_content,
		t_game *game)
{
	int		fd;
	char	*line;
	int		yaxis;

	yaxis = 0;
	game->x_axis = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (NULL);
	line = get_next_line(fd);
	while (line != NULL)
	{
		map_content = parse_line(line, map_content);
		check_x_len(line, game, map, map_content);
		free(line);
		yaxis++;
		line = get_next_line(fd);
	}
	close(fd);
	map->height = yaxis;
	map->width = game->x_axis;
	free(line);
	return (map_content);
}
