#include "libft.h"

char	*ft_strmaxjoin(char **strings, char *c)
{
	int		i;
	char	*safe;
	char	*result;

	i = -1;
	result = malloc(1);
	*result = 0;
	while (strings[++i])
	{
		safe = result;
		result = ft_strjoin(result, strings[i]);
		free(safe);
		if (strings[i + 1])
		{
			safe = result;
			result = ft_strjoin(result, c);
			free(safe);
		}
	}
	return (result);
}