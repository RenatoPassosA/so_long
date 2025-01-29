#include "so_long_bonus.h"

void	destroyer(t_game *game)
{
	mlx_destroy_image(game->mlx_ptr, game->wall.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->floor.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->collectable.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->character_up.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->character_down.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->character_left.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->character_right.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->closed_door.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->opened_door.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->on_door.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->animation.walk_left[0].xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->animation.walk_left[1].xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->animation.walk_left[2].xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->animation.walk_right[0].xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->animation.walk_right[1].xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->animation.walk_right[2].xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->animation.walk_ud[0].xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->animation.walk_ud[1].xpm_ptr);
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	mlx_destroy_display(game->mlx_ptr);
}

void	free_all(t_game *game)
{
	free_matrix(game->map->matrix, game->height);
	ft_lstclear(&(game->map_content));
	free(game->animation.walk_left);
	free(game->animation.walk_right);
	free(game->animation.walk_ud);
	free(game->mlx_ptr);
	free(game);
}

int	finish_game(t_game *game)
{
	destroyer(game);
	free_all(game);
	exit(0);
}
