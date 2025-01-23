#include "so_long.h"





void	init_mlx(t_game *game)
{
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
	sprite.x = TILE_SIZE; // Force sprite width to match tile size
	sprite.y = TILE_SIZE; // Force sprite height to match tile size
	return (sprite);
}

void	get_sprites_path(t_game *game)
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
	
}

/*void	render_player(t_game *game)
{
 
}*/

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
		render_sprite (game, game->character_right, y, x);
	else if (value == 'C')
		render_sprite (game, game->collectable, y, x);
	else if (value == 'E')
	{
		if (game->player.collected == 0)
			render_sprite (game, game->opened_door, y, x);
		else
			render_sprite (game, game->closed_door, y, x);
	}
	else if (value == 'X')
		render_sprite (game, game->on_door, y, x);
	/*else if (parameter == PLAYER)
		render_player (game, y, x);*/
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
	if (game->map->matrix[game->player.y][game->player.x].value == 'X' && game->player.collected != 0)
		return (2);
	return (0);



}

void	set_new_values(t_game *game, char direction, int closed_door)
{
	int x;
	int y;

	x = -1;
	y = -1;

	if (closed_door == 2)
	{
		y = game->player.y;
		x = game->player.x;
	}
	if (direction == 'u')
	{
		game->map->matrix[game->player.y][game->player.x].value = '0';
		game->player.y -=1;
		game->map->matrix[game->player.y][game->player.x].value = 'P';
	}
	else if (direction == 'd')
	{
		game->map->matrix[game->player.y][game->player.x].value = '0';
		game->player.y +=1;
		game->map->matrix[game->player.y][game->player.x].value = 'P';
	}
	else if (direction == 'l')
	{
		game->map->matrix[game->player.y][game->player.x].value = '0';
		game->player.x -=1;
		game->map->matrix[game->player.y][game->player.x].value = 'P';
	}
	else if (direction == 'r')
	{
		game->map->matrix[game->player.y][game->player.x].value = '0';
		game->player.x +=1;
		game->map->matrix[game->player.y][game->player.x].value = 'P';
	}
	if (closed_door == 1)
		game->map->matrix[game->player.y][game->player.x].value = 'X';
	
	if (x != -1 && y != -1)
		game->map->matrix[y][x].value = 'E';

}



int keyboard_action(int key, t_game *game)
{
	int	closed_door;

	closed_door = 0;
    if (key == 65307) // Escape key
        exit(0);
	else if (key == 65362) // Up
	{
		if (!check_boundaries(game) || !check_walls(game, 'u'))
			return (0);
		check_collectables(game, 'u');
		closed_door = check_closed_door(game, 'u');
		set_new_values(game, 'u', closed_door);
	}
    else if (key == 65364) // Down
    {
		if (!check_boundaries(game) || !check_walls(game, 'd'))
			return (0);
		check_collectables(game, 'd');
		closed_door = check_closed_door(game, 'd');
		set_new_values(game, 'd', closed_door);
	}
    else if (key == 65361) // Left
    {
		if (!check_boundaries(game) || !check_walls(game, 'l'))
			return (0);
		check_collectables(game, 'l');
		closed_door = check_closed_door(game, 'l');
		set_new_values(game, 'l', closed_door);
	}
    else if (key == 65363) // Right
    {
		if (!check_boundaries(game) || !check_walls(game, 'r'))
			return (0);
		check_collectables(game, 'r');
		closed_door = check_closed_door(game, 'r');
		set_new_values(game, 'r', closed_door);
	}
    render_map(game);
	//printf("---------------%c", game->map->matrix[game->player.y][game->player.x].value);
    return(0);
}

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
    
    game->width = map->width;
    game->height = map->height;
    game->map = map;
	game->player.collected = get_collectables(map_content);



    

    init_mlx(game);
    get_sprites_path(game);
    render_map(game);
    mlx_key_hook(game->win_ptr, keyboard_action, game);
	printf("--------------%d", game->player.collected);
    mlx_loop(game->mlx_ptr);

    return (0);


   
}