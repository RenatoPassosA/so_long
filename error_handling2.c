/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:29:14 by rpassos-          #+#    #+#             */
/*   Updated: 2025/01/30 14:29:15 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_borders(t_map *map)
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

void	put_str(char *str)
{
	int	index;

	index = 0;
	while (str[index] != '\0')
	{
		write(1, &str[index], 1);
		index++;
	}
}

void	error_msgs(int n)
{
	char	*str;

	str = NULL;
	if (n == 1)
		str = "Error.\n Map has no content";
	else if (n == 2)
		str = "Error.\n Map is not rectangular";
	else if (n == 3 || n == 4)
		str = "Error.\n More than one or no starting position or exit";
	else if (n == 5)
		str = "Error.\n No collectibles";
	else if (n == 6 || n == 7 || n == 8)
		str = "Error.\n Border is malformed";
	else if (n == 9)
		str = "Error.\n Could not reach the collectibles or the exit";
	else if (n == 10)
		str = "Error.\n One of the lines is too long";
	else if (n == 11)
		str = "Error.\n No monster or more than one monster";
	else if (n == 12)
		str = "Error.\n Forbiden values on the map";
	else if (n == 13)
		str = "Error.\n Map is too big";
	put_str(str);
}
