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




#define IMG_WIDTH 32
#define IMG_HEIGHT 32
#define TILE_SIZE 32

typedef struct player
{
	int x;
	int	y;
	int	collected;
	char direction;
	int	moves;
} t_player;

typedef struct values
{
	char value;
	int	visited;
} t_values;


typedef struct map
{
	t_values **matrix;
	int width;
	int height;
	int collectable_counter;
    int found_exit;
}	t_map;

typedef struct s_image
{
	void	*xpm_ptr;
	int		x;
	int		y;
}	t_image;

typedef struct map_content
{
	char sqm;
	struct map_content *next;
} t_map_content;

typedef struct s_game
{
    void *mlx_ptr;
    void *win_ptr;
	int width;
	int height;
	t_player player;
	t_image floor;
	t_image wall;
	t_image character_up;
	t_image character_down;
	t_image character_left;
	t_image character_right;
	t_image collectable;
	t_image closed_door;
	t_image opened_door;
	t_image on_door;
	t_map *map;
	t_map_content *map_content;
} 	t_game;	

t_map_content	*lst_new(char value);
size_t	ft_strlen(const char *str);
char	*get_next_line(int fd);
void    error_handling(t_map *map, t_map_content *content);
void    run_flood_fill(t_map *map, t_map_content *content, t_game *game);
t_map_content *read_map(char *file, t_map *map, t_map_content *map_content);
void    fill_matrix(t_map_content *map_content, t_map *map);
char			*ft_itoa(int n);
char	*ft_strjoin(char *s1, char *s2);
void	free_matrix(t_values **matrix, int y);
void	ft_lstclear(t_map_content **map_content);


#endif