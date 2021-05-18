#include "libft.h"

char    **ft_append_element(char **matrix, char *element)
{
    int     i;
    char    **result;

    if (!matrix)
    {
        result = malloc(2 * sizeof(char *));
        result[0] = element;
        result[1] = 0;
        return (result);
    }
    i = 0;
    while (matrix[i])
        i++;
    result = malloc((i + 2) * sizeof(char *));
    i = -1;
    while (matrix[++i])
        result[i] = matrix[i];
    result[i++] = element;
    result[i] = 0;
    free(matrix);
    return (result);
}