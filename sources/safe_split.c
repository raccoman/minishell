#include "minishell.h"

void    jump_quote(char *input, int *i, char type)
{
    (*i)++;
    if (type == '\'')
    {
        while (input[*i] != '\'')
            (*i)++;
    }
    else if (type == '\"')
    {
        while (input[*i] != '\"' && input[*i - 1] != '\\')
            (*i)++;
    }
    (*i)++;
}

char    **add_splitted(char **splitted, char *new)
{
    int     i;
    char    **safe;

    i = 0;
    while (splitted[i])
        i++;
    safe = malloc((i + 2) * sizeof(char *));
    i = -1;
    while (splitted[++i])
        safe[i] = splitted[i];
    safe[i++] = new;
    safe[i] = 0;
    free(splitted);
    return (safe);    
}

char    **safe_split(char *input, char del)
{
    char    **splitted;
    int     i;
    int     start;
    char    *new;

    splitted = malloc(sizeof(char *));
    *splitted = 0;
    i = 0;
    start = 0;
    while (input[i])
    {
        if (input[i] == '\\')
            i += 2;
        if (input[i] == '\'')
            jump_quote(input, &i, '\'');
        if (input[i] == '\"')
            jump_quote(input, &i, '\"');
        if (input[i] == del || !input[i])
        {
            new = malloc((i - start + 1) * sizeof(char));
            start = ++i;
            ft_strlcpy(new, input + start, sizeof(new));
            splitted = add_splitted(splitted, new);
        }
        else
            i++;
    }
    return (splitted);
}