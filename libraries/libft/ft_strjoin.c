#include "libft.h"

char	*ft_strjoin(char *str1, char *str2)
{
	char	*rslt;
	int		i;

	i = 0;
	rslt = malloc(ft_strlen(str1) + ft_strlen(str2) + 1);
	if (!rslt)
		return (NULL);
	while (str1 && *str1)
		rslt[i++] = *str1++;
	while (str2 && *str2)
		rslt[i++] = *str2++;
	rslt[i] = 0;
	return (rslt);
}