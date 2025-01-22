#include "so_long.h"


t_map_content	*lst_new(char value)
{
	t_map_content	*node;

	node = (t_map_content *)malloc(sizeof(t_map_content));
	if (!node)
		return (NULL);
	node->sqm = value;
    node->next = NULL;
	return (node);
}

size_t	ft_strlen(const char *str)
{
	size_t	counter;

	counter = 0;
	while (str && str[counter] != '\0')
		counter++;
	return (counter);
}