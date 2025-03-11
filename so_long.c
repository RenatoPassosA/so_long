/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:28:53 by rpassos-          #+#    #+#             */
/*   Updated: 2025/01/30 14:28:55 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	write_movements(t_game *game)
{
	char	*s;
	char	*phrase;

	s = ft_itoa(game->player.moves);
	phrase = ft_strjoin("Movements: ", s);
	write(1, phrase, ft_strlen(phrase));
	write(1, "\n", 1);
	free(s);
	free(phrase);
	render_map(game);
}

int	check_argument(int ac, char **av)
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

int	main(int ac, char **av)
{
	t_game			*game;
	t_map			*map;
	t_map_content	*map_content;

	if (!check_argument(ac, av))
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
	clear_data(map, map_content, game, 1);
	return (0);
}
