#include "minishell.h"

char    *parse_priorities(char *input)
{
    char    *string;

    string = ft_strdup(input);
    ft_replace(&string, "&&", ";");
    ft_replace(&string, "||", ";");
    ft_replace(&string, "(", NULL);
    ft_replace(&string, ")", NULL);
    return (string);
}

int     shortlen(char *string)
{
    int len;
    int c;

    len = ft_strlen(string);
    c = len;
    while (string[--c] == ' ')
        len--;
    c = 0;
    while (string[c++] == ' ')
        len--;
    return (len);
}

int skip_block(char *string, int *i)
{
    int     asd;
    int     fgh;
    char    *copy;

    asd = 0;
    fgh = 1;
    while (string[fgh])
    {
        if (string[fgh] == ')' && asd == 0)
            break ;
        else if (string[fgh] == ')')
            asd--;
        else if (string[fgh] == '(')
            asd++;
        fgh++;
    }
    copy = ft_strndup(string, fgh);
    (*i) += ft_count_str(copy, "&&");
    (*i) += ft_count_str(copy, "||");
    (*i) += 1;
    return (fgh + 1);
}

void	execute_semicols(t_minishell *minishell)
{
    int j;
    int k;
	int	i;
    int lvl;
    int status[100];

    j = 0;
    k = 0;
	i = 0;
    lvl = 0;
	while (minishell->semicols[i])
	{
		


        while (minishell->o_input[k] == ' ')
            k++;

        if (minishell->o_input[k] == '(')
        {

            if ((j == 2 && status[lvl] == 0) || (j == 1 && status[lvl] != 0))
            {  
                int a = skip_block(minishell->o_input + k, &i);
				k += a;
                free(minishell->input);
                continue ;
            }
            else
            {
                status[lvl + 1] = status[lvl];
                lvl++;
                k++;
            }
        }
        else if (minishell->o_input[k] == ')')
        {
            status[lvl - 1] = status[lvl];
            lvl--;
            k++;
			continue ;
        }
		minishell->input = ft_strdup(minishell->semicols[i++]);
        
        while (minishell->o_input[k] == ' ')
            k++;

		//printf ("%s\t", minishell->o_input + k);
		if (!strncmp(minishell->o_input + k, "&&", 2))
        {
            j = 1;
            k += 2;
        }
        else if (!strncmp(minishell->o_input + k, "||", 2))
        {
            j = 2;
            k += 2;
        }
        else if (!strncmp(minishell->o_input + k, ";", 1))
        {
            j = 0;
            k += 1;
        }

		while (minishell->o_input[k] == ' ')
            k++;
        
        k += shortlen(minishell->input);

        while (minishell->o_input[k] == ' ')
            k++;

		//printf("STATUS: %d -- j: %d\n", status[lvl], j);
			
		if (j == 0 || (j == 1 && status[lvl] == 0))
        { 
            parse_input(minishell);
		    executor(minishell, minishell->command);
            status[lvl] = ft_atoi(get_env_value(minishell, "?"));
        }
        else if (j == 2 && status[lvl] != 0)
        {
            parse_input(minishell);
		    executor(minishell, minishell->command);
            status[lvl] = ft_atoi(get_env_value(minishell, "?"));
        }

        if (!strncmp(minishell->o_input + k, "&&", 2))
        {
            j = 1;
            k += 2;
        }
        else if (!strncmp(minishell->o_input + k, "||", 2))
        {
            j = 2;
            k += 2;
        }
        else if (!strncmp(minishell->o_input + k, ";", 1))
        {
            j = 0;
            k += 1;
        }
        free(minishell->input);
	}
}