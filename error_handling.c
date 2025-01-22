
#include "so_long.h"

void map_size(t_map *map)
{
    if (map->height == 0 || map->width == 0)
        printf("Error\nsem conteudo");
    if (map->height == map->width)
        printf("Error\nmapa não retangular");
}

void    map_counter(t_map_content *content)
{
    int player_counter;
    int exit_counter;
    int collect_counter;

    player_counter = 0;
    exit_counter = 0;
    collect_counter = 0;
    while(content->next != NULL)
    {
        if (content->sqm == 'P')
            player_counter++;
        if (content->sqm == 'E')
            exit_counter++;
        if (content->sqm == 'C')
        collect_counter++;
        content = content->next;
    }
    if (player_counter != 1)
        printf("Error\nmais de uma ou nenhuma posição inicial");
    if (exit_counter != 1)
        printf("Error\nmais de uma ou nenhuma saida");
    if (collect_counter == 0)
        printf("Error\nnão há coletáveis");
    return ;
}

void    check_borders(t_map *map)
{
    int y;
    int index;
    
    y = 0;
    index = 0;
    while (y < map->height)
    {
        if (map->matrix[y][0] != '1' || map->matrix[y][map->width - 1] != '1')
            printf("Error\n mapa fora de formato laterallll");
        y++;   
    }
    while (index < map->width)
    {
        if (map->matrix[0][index] != '1')
            printf("Error\n mapa fora de formato lateral\n");
        if (map->matrix[map->height - 1][index] != '1')
            printf("Error\n mapa fora de formato superior/inferior");
        index++;
    }
}

void    error_handling(t_map *map, t_map_content *content)
{
    map_size(map);
    map_counter(content);
    check_borders(map);
}

