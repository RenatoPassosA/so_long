#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include "../mlx/mlx.h"
# include <fcntl.h>
# include <stddef.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define IMG_WIDTH 32
# define IMG_HEIGHT 32
# define TILE_SIZE 32

typedef struct monster
{
	int					x;
	int					y;
	char				direction;
	int					move_check;
	int					on_collectable;
}						t_monster;

typedef struct player
{
	int					x;
	int					y;
	int					collected;
	char				direction;
	int					moves;
}						t_player;

typedef struct values
{
	char				value;
	int					visited;
}						t_values;

typedef struct map
{
	t_values			**matrix;
	int					width;
	int					height;
	int					collectable_counter;
	int					found_exit;
}						t_map;

typedef struct s_image
{
	void				*xpm_ptr;
	int					x;
	int					y;
}						t_image;

typedef struct map_content
{
	char				sqm;
	struct map_content	*next;
}						t_map_content;

typedef struct s_sprites
{
	t_image				*walk_right;
	t_image				*walk_ud;
	t_image				*walk_left;
	int					current_r;
	int					current_l;
	int					current_ud;
}						t_sprites;

typedef struct s_game
{
	void				*mlx_ptr;
	void				*win_ptr;
	int					width;
	int					height;
	int					num_monsters;
	int					end_game;
	int					count_p;
	int					count_e;
	int					count_c;
	int					count_m;
	t_player			player;
	t_monster			monster;
	t_sprites			animation;
	t_image				floor;
	t_image				wall;
	t_image				character_up;
	t_image				character_down;
	t_image				character_left;
	t_image				character_right;
	t_image				monster_left;
	t_image				monster_right;
	t_image				collectable;
	t_image				closed_door;
	t_image				opened_door;
	t_image				on_door;
	t_map				*map;
	t_map_content		*map_content;
}						t_game;

t_map_content			*lst_new(char value);
size_t					ft_strlen(const char *str);
char					*get_next_line(int fd);
void					error_handling(t_map *map, t_map_content *content,
							t_game *game);
void					run_flood_fill(t_map *map, t_map_content *content,
							t_game *game);
t_map_content			*read_map(char *file, t_map *map,
							t_map_content *map_content, t_game *game);
void					fill_matrix(t_map_content *map_content, t_map *map);
char					*ft_itoa(int n);
char					*ft_strjoin(char *s1, char *s2);
void					free_matrix(t_values **matrix, int y);
void					ft_lstclear(t_map_content **map_content);
void					clear_data(t_map *map, t_map_content *map_content,
							t_game *game, int n);
void					error_msgs(int n);
int						get_the_player(t_game *game);
char					get_value(t_game *game, int y, int x);
int						render_map(t_game *game);
void					random_monster_move(t_game *game);
int						finish_game(t_game *game);
void					check_surrounding(t_game *game);
void					put_str(char *str);
int						keyboard_action(int key, t_game *game);
void					init_mlx(t_game *game, t_map *map);
void					start_data(t_game *game, t_map *map,
							t_map_content *map_content);
int						map_size(t_map *map);
void					show_movements(t_game *game);
int						check_boundaries(t_game *game);
int						check_walls(t_game *game, char direction);
void					check_collectables(t_game *game, char direction);
int						check_closed_door(t_game *game, char direction);
int						check_monster_walls(t_game *game, char direction);
void					monster_move(t_game *game, char dir);
int						check_monster_boundaries(t_game *game);
char					*ft_strnstr(const char *big, const char *little,
							size_t len);

#endif