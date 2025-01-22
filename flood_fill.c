#include "so_long.h"

int    collectables_counter(t_map_content *content)
{
    int collect_counter;

    collect_counter = 0;
    while(content->next != NULL)
    {
        if (content->sqm == 'C')
        collect_counter++;
        content = content->next;
    }
    return (collect_counter);
}

int *get_starter_position(t_map *map)
{
    int *coordinates;
    int x;
    int y;

    x = 0;
    y = 0;
    coordinates = (int *)malloc(sizeof(int) * 2);
    if (!coordinates)
        return (NULL);
    while (y < map->height)
    {
        while(x < map->width)
        {
            if (map->matrix[y][x] == 'P')
            {
                coordinates[0] = y;
                coordinates[1] = x;
                return (coordinates);
            }
            x++;
        }
        x = 0;
        y++;
    }
    return (NULL);
}

void    flood_fill(t_map *map, int y, int x)
{
 
   
    if (x < 0 || y < 0 || x >= map->width || y >= map->height)
        return;
    if (map->matrix[y][x] == '1' || map->matrix[y][x] == 'V')
        return;    
    if (map->matrix[y][x] == 'C')
        map->collectable_counter++;
    if (map->matrix[y][x] == 'E')
        map->found_exit = 1;
    if (map->matrix[y][x] != 'P')
        map->matrix[y][x] = 'V';
    flood_fill(map, y, x + 1);
    flood_fill(map, y, x - 1);
    flood_fill(map, y + 1, x);
    flood_fill(map, y - 1, x);
}

void    run_flood_fill(t_map *map, t_map_content *content)
{
    int *starter_position;
    int y;
    int x;
    int colletables_in_map;

    starter_position = get_starter_position(map);
    y = starter_position[0];
    x = starter_position[1];
    free(starter_position);
    map->collectable_counter = 0;
    map->found_exit = 0;
    flood_fill(map, y, x);
    colletables_in_map = collectables_counter(content);
    if (map->collectable_counter != colletables_in_map)
        printf("Error\nNão alcançou os coletáveis");
    if (map->found_exit != 1)
        printf("Error\nNão alcançou a saída");
}