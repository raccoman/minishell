#include "libft.h"

int	ft_count(char *string, int c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (string && string[i])
	{
		if (string[i] == c)
			count++;
		i++;
	}
	return (count);
}