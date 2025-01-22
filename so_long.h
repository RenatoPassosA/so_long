#ifndef SO_LONG_H
# define SO_LONG_H

#include "mlx/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stddef.h>
#include <string.h>
#include <math.h>
#include <limits.h>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct map
{
	char **matrix;
	int width;
	int height;
	int collectable_counter;
    int found_exit;
}	t_map;

typedef struct map_content
{
	char sqm;
	struct map_content *next;
} t_map_content;

t_map_content	*lst_new(char value);
size_t	ft_strlen(const char *str);
char	**ft_split(char const *s, char c);
char	*get_next_line(int fd);
int	count_words(char *s, char c);
void    error_handling(t_map *map, t_map_content *content);
void run_flood_fill(t_map *map, t_map_content *content);

#endif