#include "so_long.h"

static int	get_digits(int n)
{
	int	i;

	i = 1;
	while (n /= 10)
		i++;
	return (i);
}

char			*ft_itoa(int n)
{
	char		*s;
	int		digits;
	
	digits = get_digits(n);
	if (!(s = (char *)malloc(sizeof(char) * (digits + 1))))
		return (NULL);
	*(s + digits) = 0;
	while (digits--)
	{
		*(s + digits) = n % 10 + '0';
		n = n / 10;
	}
	return (s);
}