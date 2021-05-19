#include "libft.h"

short   ft_onlythischar(char *str, char c)
{
	while (*str)
	{
		if (*str++ != c)
			return (0);
	}
	return (1);
}