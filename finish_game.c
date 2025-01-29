#include "so_long.h"

void	clear_data(t_map *map, t_map_content *map_content, t_game *game, int n)
{
	free_matrix(map->matrix, map->height - 1);
	error_msgs(n);
	ft_lstclear(&map_content);
	free(game);
	exit(0);
}

int	finish_game(t_game *game)
{
	mlx_destroy_image(game->mlx_ptr, game->floor.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->wall.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->character_up.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->character_down.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->character_left.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->character_right.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->collectable.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->closed_door.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->opened_door.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->on_door.xpm_ptr);
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	free_matrix(game->map->matrix, game->height);
	ft_lstclear(&(game->map_content));
	mlx_destroy_display(game->mlx_ptr);
	free(game->mlx_ptr);
	free(game);
	exit(0);
}
