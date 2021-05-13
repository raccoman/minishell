#include "libft.h"

char	*new_string(char c)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	if (!str)
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

char	*ft_append(char *str, char c)
{
	char	*new_str;
	int	i;

	if (!str)
		return (new_string(c));
	i = 0;
	new_str = malloc(sizeof(char) * (ft_strlen(str) + 2));
	while (str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = c;
	i++;
	new_str[i] = 0;
	free(str);
	return (new_str);
}