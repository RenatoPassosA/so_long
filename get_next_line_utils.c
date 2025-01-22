/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:08:06 by rpassos-          #+#    #+#             */
/*   Updated: 2024/11/06 18:08:08 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*concat(char *final, char *str, int index)
{
	int	strindex;

	strindex = 0;
	while (str[strindex] != '\0')
	{
		final[index] = str[strindex];
		index++;
		strindex++;
	}
	return (final);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		size;
	int		index;
	char	*str;

	if (!s1 && !s2)
		return (NULL);
	index = 0;
	size = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	str = (char *)malloc(size * sizeof(char) + 1);
	if (!str)
		return (NULL);
	if (s1)
		str = concat(str, (char *)s1, index);
	index = ft_strlen((char *)s1);
	if (s2)
		str = concat(str, (char *)s2, index);
	index = index + ft_strlen((char *)s2);
	str[index] = '\0';
	free(s1);
	return (str);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*substr;
	int		substrsize;
	int		index;

	if (!s)
		return (NULL);
	substrsize = len;
	if (len > ft_strlen((char *)s) - start)
		substrsize = ft_strlen((char *)s) - start;
	if (len == 0 || start > ft_strlen((char *)s))
	{
		substr = (char *)malloc(sizeof(char));
		*substr = '\0';
		return (substr);
	}
	index = 0;
	substr = (char *)malloc(sizeof(char) * (substrsize + 1));
	if (substr == NULL)
		return (NULL);
	while (substrsize-- > 0 && s[start] != '\0')
		substr[index++] = s[start++];
	substr[index] = '\0';
	return (substr);
}

char	*ft_strchr(const char *s, int c)
{
	char	letter;

	letter = c;
	if (!c)
		return ((char *)s + ft_strlen((char *)s));
	while (1)
	{
		if (*s == letter)
			return ((char *)s);
		else if (*s == '\0' && c != '\0')
			return (NULL);
		else if (*s == '\0')
			return ((char *)s);
		s++;
	}
}

char	*ft_strdup(char *str)
{
	int		size;
	int		index;
	char	*dest;

	if (!str)
		return (NULL);
	size = ft_strlen(str);
	index = 0;
	dest = (char *)malloc(sizeof(char) * size + 1);
	if (dest == NULL)
		return (NULL);
	while (str[index])
	{
		dest[index] = str[index];
		index++;
	}
	dest[index] = '\0';
	return (dest);
}
