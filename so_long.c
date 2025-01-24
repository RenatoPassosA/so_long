#include "so_long.h"



int	get_collectables(t_map_content *map_content)
{
	int	counter;

	counter = 0;

	while (map_content != NULL)
	{
		if (map_content->sqm == 'C')
			counter++;
		map_content = map_content->next;
	}
	return (counter);
}

void	init_mlx(t_game *game, t_map *map)
{
	game->width = map->width;
    game->height = map->height;
	game->mlx_ptr = mlx_init();
	if (game->mlx_ptr == NULL)
	{
		free(game->mlx_ptr);
		printf("Couldn't find mlx pointer. Try it using a VNC.");
	}
	game->win_ptr = mlx_new_window(game->mlx_ptr, game->width * IMG_WIDTH, game->height * IMG_HEIGHT, "so_long"); 
	if (game->win_ptr == NULL)
	{
		free(game->mlx_ptr);
		printf("Couldn't create the Window.");
	}
	
}

t_image	new_sprite(void *mlx, char *path)
{
	t_image	sprite;

	sprite.xpm_ptr = mlx_xpm_file_to_image(mlx, path, &sprite.x, &sprite.y);
	if (sprite.xpm_ptr == NULL)
		printf("Couldn't find a sprite. Does it exist?");
	sprite.x = TILE_SIZE;
	sprite.y = TILE_SIZE;
	return (sprite);
}

void	start_data(t_game *game, t_map *map, t_map_content *map_content)
{
	void	*mlx;

	mlx = game->mlx_ptr;
    game->wall = new_sprite(mlx, "images/wall.xpm");
	game->floor = new_sprite(mlx, "images/grass.xpm");
	game->collectable = new_sprite(mlx, "images/collectable.xpm");
	game->character_up = new_sprite(mlx, "images/up.xpm");
	game->character_down = new_sprite(mlx, "images/down.xpm");
	game->character_left = new_sprite(mlx, "images/left.xpm");
	game->character_right = new_sprite(mlx, "images/right.xpm");
	game->closed_door = new_sprite(mlx, "images/closed_door.xpm");
	game->opened_door = new_sprite(mlx, "images/opened_door.xpm");
	game->on_door = new_sprite(mlx, "images/on_door.xpm");
    game->map = map;
	game->map_content = map_content;
	game->player.collected = get_collectables(map_content);
	game->player.moves = 0;
	game->player.direction = 'r';
}

void	render_player_direction(t_game *game, int line, int column)
{
	if (game->player.direction == 'u')
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->character_up.xpm_ptr, column * TILE_SIZE, line * TILE_SIZE);
	if (game->player.direction == 'd')
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->character_down.xpm_ptr, column * TILE_SIZE, line * TILE_SIZE);
	if (game->player.direction == 'l')
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->character_left.xpm_ptr, column * TILE_SIZE, line * TILE_SIZE);
	if (game->player.direction == 'r')
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->character_right.xpm_ptr, column * TILE_SIZE, line * TILE_SIZE);
}

void	render_sprite(t_game *game, t_image sprite, int line, int column)
{
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, sprite.xpm_ptr, column * TILE_SIZE, line * TILE_SIZE);
}

void	check_sprite(t_game *game, int y, int x)
{	
	char	value;

	value = game->map->matrix[y][x].value;
	if (value == '0')
        render_sprite (game, game->floor, y, x);
	else if (value == '1')
		render_sprite (game, game->wall, y, x);
	else if (value == 'P')
		render_player_direction (game, y, x);
	else if (value == 'C')
		render_sprite (game, game->collectable, y, x);
	else if (value == 'E')
	{
		if (game->player.collected == 0)
		{
			render_sprite (game, game->opened_door, y, x);
			game->map->matrix[y][x].value = 'F';
		}
		else
			render_sprite (game, game->closed_door, y, x);
	}
	else if (value == 'X')
		render_sprite (game, game->on_door, y, x);
}

int	render_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			check_sprite(game, y, x);
			x++;
		}
		y++;
	}
	return (0);
}

int	check_boundaries (t_game *game)
{
	if ((game->player.y <= 0 || game->player.y >= game->height - 1))
			return (0);
	if ((game->player.x <= 0 || game->player.x >= game->width - 1))
			return (0);		
	return (1);
}

char 	get_value(t_game *game, int y, int x)
{
	return (game->map->matrix[y][x].value);
}

int	check_walls(t_game *game, char direction)
{
	char s;

	if (direction == 'u')
		s = get_value(game, game->player.y - 1, game->player.x);
	else if (direction == 'd')
		s = get_value(game, game->player.y + 1, game->player.x);
	else if (direction == 'l')
		s = get_value(game, game->player.y, game->player.x - 1);
	else if (direction == 'r')
		s = get_value(game, game->player.y, game->player.x + 1);
	if (s == '1')
		return (0);
	else
		return (1);
}

int	finish_game(t_game *game) // ALTERAR
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
	free_matrix(game->map->matrix, game->height - 1);
	ft_lstclear(&(game->map_content));
	printf("VENCEU CARAIO");
	exit(0);
}

void check_collectables(t_game *game, char direction)
{
	char s;

	if (direction == 'u')
		s = get_value(game, game->player.y - 1, game->player.x);
	else if (direction == 'd')
		s = get_value(game, game->player.y + 1, game->player.x);
	else if (direction == 'l')
		s = get_value(game, game->player.y, game->player.x - 1);
	else if (direction == 'r')
		s = get_value(game, game->player.y, game->player.x + 1);
	if (s == 'C')
		game->player.collected--;
}

int	check_closed_door(t_game *game, char direction)
{
	char s;

	if (direction == 'u')
		s = get_value(game, game->player.y - 1, game->player.x);
	else if (direction == 'd')
		s = get_value(game, game->player.y + 1, game->player.x);
	else if (direction == 'l')
		s = get_value(game, game->player.y, game->player.x - 1);
	else if (direction == 'r')
		s = get_value(game, game->player.y, game->player.x + 1);
	if (s == 'E' && game->player.collected != 0)
		return (1);
	if (s == 'X' && game->player.collected != 0)
		return (2);
	if (s == 'F')
		return (3);
	return (0);
}

void change_value(t_game *game, char direction, int closed_door)
{
	if (direction == 'u')
		game->player.y -= 1;
	else if (direction == 'd')
		game->player.y += 1;
	else if (direction == 'l')
		game->player.x -= 1;
	else if (direction == 'r')
		game->player.x += 1;
	if (closed_door == 3)
		finish_game(game);
}

void	set_new_values(t_game *game, char direction, int closed_door)
{
	int prev_x;
	int prev_y;
	int x; 
	int y;

	prev_x = game->player.x;
	prev_y = game->player.y;
	x = -1;
	y = -1;
	change_value(game, direction, closed_door);
	if (closed_door == 2)
	{
		y = prev_y;
		x = prev_x;
	}
	if (game->map->matrix[prev_y][prev_x].value == 'X') // em cima da porta fechada
		game->map->matrix[prev_y][prev_x].value = 'E';  // volta porta fechada
	else
		game->map->matrix[prev_y][prev_x].value = '0';
	if (closed_door == 1) // jogador está em cima da porta e nao coletou tudo
		game->map->matrix[game->player.y][game->player.x].value = 'X'; // Jogador está na porta
	else
		game->map->matrix[game->player.y][game->player.x].value = 'P'; // Jogador está no chão normal
	if (x != -1 && y != -1)
		game->map->matrix[y][x].value = 'E';
}

void actions(t_game *game, char dir, int *check_movement)
{
	int	closed_door;

	closed_door = 0;
	if (!check_boundaries(game) || !check_walls(game, dir))
			return ;
	check_collectables(game, dir);
	closed_door = check_closed_door(game, dir);
	set_new_values(game, dir, closed_door);
	game->player.direction = dir;
	game->player.moves++;
	*check_movement = 1;
}

int keyboard_action(int key, t_game *game) //NORM
{
	char *s;
	char *phrase;
	int	check_movement;

	check_movement = 0;
    if (key == 65307) // esc
        finish_game(game);
	else if (key == 119) // w
		actions(game, 'u', &check_movement);
    else if (key == 115) // s
    	actions(game, 'd', &check_movement);
    else if (key == 97) // a
		actions(game, 'l', &check_movement);
    else if (key == 100) // Right
    	actions(game, 'r', &check_movement);
	if (check_movement)
    {
        s = ft_itoa(game->player.moves);
        phrase = ft_strjoin("Movements: ", s);
        write(1, phrase, ft_strlen(phrase)); //ACERTAR A QUEBRA DE LINHA
        free(s);
        free(phrase);
        render_map(game);
    }
    return(0);
}

int main(int ac, char **av)
{
    t_game *game;
    t_map *map;
    t_map_content *map_content;

    map = (t_map *)malloc(sizeof(t_map));;
    map_content = NULL;
    game = (t_game *)malloc(sizeof(t_game));;
    if (ac != 2)
    {
        printf("Error parametros\n");   
        return (0);
    }
    map_content = read_map(av[1], map, map_content);
    fill_matrix(map_content, map);
    error_handling(map, map_content);
    run_flood_fill(map, map_content, game);
    init_mlx(game, map);
    start_data(game, map, map_content);
    render_map(game);
    mlx_key_hook(game->win_ptr, keyboard_action, game);
	mlx_hook(game->win_ptr, 17, 0, finish_game, NULL);
    mlx_loop(game->mlx_ptr);
    return (0);
}