/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:29:32 by rpassos-          #+#    #+#             */
/*   Updated: 2025/01/30 14:29:33 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	get_digits(int n)
{
	int	i;

	i = 1;
	while (n)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*s;
	int		digits;

	digits = get_digits(n);
	s = (char *)malloc(sizeof(char) * (digits + 1));
	if (!s)
		return (NULL);
	*(s + digits) = 0;
	while (digits--)
	{
		*(s + digits) = n % 10 + '0';
		n = n / 10;
	}
	return (s);
}

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

void	ft_lstclear(t_map_content **map_content)
{
	t_map_content	*current;
	t_map_content	*next_node;

	if (!map_content || !*map_content)
		return ;
	current = *map_content;
	while (current)
	{
		next_node = current->next;
		free(current);
		current = next_node;
	}
	free(current);
	*map_content = NULL;
}
