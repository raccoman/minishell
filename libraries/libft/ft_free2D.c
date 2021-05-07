#include "libft.h"

void	ft_free2D(void **buffer)
{
	int				i;
	unsigned char	**mem;

	if (buffer != NULL)
	{
		i = 0;
		mem = (unsigned char **)buffer;
		while (mem[i] != 0)
			free(mem[i++]);
		free(mem);
	}
}