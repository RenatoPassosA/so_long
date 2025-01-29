#include "so_long_bonus.h"

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
	else if (n == 6)
		str = "Error.\n Left or right border is malformed";
	else if (n == 7)
		str = "Error.\n Map is misaligned on the sides";
	else if (n == 8)
		str = "Error.\n Map is misaligned on top/bottom";
	else if (n == 9)
		str = "Error.\n Could not reach the collectibles or the exit";
	else if (n == 10)
		str = "Error.\n One of the lines is too long";
	else if (n == 11)
		str = "Error.\n No monster or more than one monster";
	put_str(str);
}

int	map_size(t_map *map)
{
	if (map->height == 0 || map->width == 0)
		return (1);
	if (map->height == map->width)
		return (2);
	return (0);
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
