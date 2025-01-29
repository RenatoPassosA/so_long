#include "so_long.h"

int	map_size(t_map *map)
{
	if (map->height == 0 || map->width == 0)
		return (1);
	if (map->height == map->width)
		return (2);
	return (0);
}

int	map_counter(t_map_content *map_content)
{
	int	player_counter;
	int	exit_counter;
	int	collect_counter;

	player_counter = 0;
	exit_counter = 0;
	collect_counter = 0;
	while (map_content->next != NULL)
	{
		if (map_content->sqm == 'P')
			player_counter++;
		if (map_content->sqm == 'E')
			exit_counter++;
		if (map_content->sqm == 'C')
			collect_counter++;
		map_content = map_content->next;
	}
	if (player_counter != 1)
		return (3);
	if (exit_counter != 1)
		return (4);
	if (collect_counter == 0)
		return (5);
	return (0);
}

void	error_handling(t_map *map, t_map_content *map_content, t_game *game)
{
	int	n;

	n = map_size(map);
	if (n != 0)
		clear_data(map, map_content, game, n);
	n = map_counter(map_content);
	if (n != 0)
		clear_data(map, map_content, game, n);
	n = check_borders(map);
	if (n != 0)
		clear_data(map, map_content, game, n);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	sign;

	if (little[0] == '\0')
		return ((char *)big);
	i = 0;
	while (big[i] && i < len)
	{
		sign = 0;
		if (big[i] == little[sign])
		{
			while (i + sign < len && big[i + sign] == little[sign])
			{
				sign++;
				if (little[sign] == '\0')
					return ((char *)&big[i]);
			}
		}
		i++;
	}
	return (0);
}
