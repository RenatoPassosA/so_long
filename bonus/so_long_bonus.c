#include "so_long_bonus.h"

int	check_argument(int ac, char **av, t_game *game)
{
	int	len;

	if (ac != 2)
	{
		put_str("Error.\n Check the arguments");
		return (0);
	}
	len = ft_strlen(av[1]);
	if (ft_strnstr(&av[1][len - 4], ".ber", 4) == NULL)
	{
		put_str("Error.\n Invalid map file");
		return (0);
	}
	return (1);
}

void	show_movements(t_game *game)
{
	char	*movements;
	char	*phrase;

	movements = ft_itoa(game->player.moves);
	phrase = ft_strjoin("Movements : ", movements);
	mlx_string_put(game->mlx_ptr, game->win_ptr, 10, 15, 0xFFFFFF, phrase);
	mlx_string_put(game->mlx_ptr, game->win_ptr, 11, 15, 0xFFFFFF, phrase);
	mlx_string_put(game->mlx_ptr, game->win_ptr, 11, 16, 0xFFFFFF, phrase);
	mlx_string_put(game->mlx_ptr, game->win_ptr, 10, 16, 0xFFFFFF, phrase);
	free(movements);
	free(phrase);
}

int	main(int ac, char **av)
{
	t_game			*game;
	t_map			*map;
	t_map_content	*map_content;

	if (!check_argument(ac, av, game))
		return (0);
	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (0);
	map_content = NULL;
	game = (t_game *)malloc(sizeof(t_game));
	if (!game)
		return (0);
	map_content = read_map(av[1], map, map_content, game);
	fill_matrix(map_content, map);
	error_handling(map, map_content, game);
	run_flood_fill(map, map_content, game);
	init_mlx(game, map);
	start_data(game, map, map_content);
	render_map(game);
	mlx_key_hook(game->win_ptr, keyboard_action, game);
	mlx_hook(game->win_ptr, 17, 0, finish_game, game);
	mlx_loop(game->mlx_ptr);
	return (0);
}
