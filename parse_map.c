#include "so_long.h"


t_map_content *parse_line(char *line, t_map_content *map_content)
{
    int index;
    t_map_content *current;
    t_map_content *new_node;
  
    index = 0;
    if (!map_content)
    {
        map_content = lst_new(line[index]);
        index++;
    }
    current = map_content;
    while (current->next != NULL)
        current = current->next;
    while (line[index] != '\0')
    {
        new_node = lst_new(line[index]);
        current->next = new_node;
        current = current->next;
        index++;
        if (line[index] == '\n')
            index++;
    }
    return (map_content);
}


void check_x_len(char *line, int *xaxis)
{   
    size_t len;
    
    len = ft_strlen(line); //14

    if (line[len - 1] == '\n') // Se a linha terminar com '\n', ignore-o na contagem
        len--;
    if (*xaxis == 0)
        *xaxis = len;
    else if (*xaxis != (int)len)
    {
        printf("ERROR, MAPA FORA DO FORMATO\n");
    }
}

void free_matrix(t_values **matrix, int y)
{
    int i;

    i = 0;
    while (i < y)
    {
        free(matrix[i]);
        i++;
    }
    free(matrix);
}

void    fill_matrix(t_map_content *map_content, t_map *map)
{
    int x;
    int y;

    x = 0;
    y = 0;
    map->matrix = (t_values **)malloc(sizeof(t_values *) * map->height);
    if (!map->matrix)
        return ;
    while (y < map->height)
    {
        map->matrix[y] = (t_values *)malloc(sizeof(t_values) * map->width);
        if (!map->matrix[y])
        {
            free_matrix(map->matrix, y);
            return ;
        }
        while(x < map->width)
        {
            map->matrix[y][x].value = map_content->sqm;
            map->matrix[y][x].visited = 0;
            map_content = map_content->next;
            x++;
        }
        x = 0;
        y++;
    }
}

t_map_content *read_map(char *file, t_map *map, t_map_content *map_content)
{
    int fd;
    char *line;
    int yaxis;
    int xaxis;

    yaxis = 0;
    xaxis = 0;
    fd = open(file, O_RDONLY);
    if (fd == -1)
        return (NULL);
    while ((line = get_next_line(fd)) != NULL)
    {
        map_content = parse_line(line, map_content);
        check_x_len(line, &xaxis);
        free(line);
        yaxis++;
    }
    close(fd);
    map->height = yaxis;
    map->width = xaxis;
    //printf("-------%d------------%d", map->width, map->height);
    free(line);
    return (map_content);
}
