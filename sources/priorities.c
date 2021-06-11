/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priorities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordanraccoman <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 19:25:23 by mgiordan          #+#    #+#             */
/*   Updated: 2021/06/10 19:25:25 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_priorities(t_minishell *sh)
{
	sh->o_input = ft_strdup(sh->input);
	if (!(*sh->input))
		return ;
	ft_replace(&sh->o_input, " ", NULL);
	ft_replace(&sh->input, "&&", ";");
	ft_replace(&sh->input, "||", ";");
	ft_replace(&sh->input, "(", NULL);
	ft_replace(&sh->input, ")", NULL);
}

int	skip_block(char *string, int *i)
{
	int		lvl;
	int		j;
	char	*copy;

	lvl = 0;
	j = 0;
	while (string[j])
	{
		if (string[j] == ')' && !lvl)
			break ;
		else if (string[j] == ')')
			lvl--;
		else if (string[j] == '(')
			lvl++;
		j++;
	}
	copy = ft_strndup(string, j);
	(*i) += ft_count_str(copy, "&&") + ft_count_str(copy, "||") + 1;
	free(copy);
	return (++j);
}

int	which_operator(char **o_input)
{
	int	and_or;

	and_or = 0;
	if (!ft_strncmp(*o_input, "&&", 2))
	{
		and_or = 1;
		*o_input += 2;
	}
	else if (!ft_strncmp(*o_input, "||", 2))
	{
		and_or = 2;
		*o_input += 2;
	}
	else if (**o_input == ';')
		(*o_input)++;
	return (and_or);
}

void	actual_exec_semicols(t_minishell *minishell,
	int i, int and_or, int *status)
{
	minishell->input = ft_strdup(minishell->semicols[i]);
	if (!and_or || (and_or == 1 && !(*status)) || (and_or == 2 && *status))
	{
		parse_input(minishell);
		executor(minishell, minishell->command);
		*status = ft_atoi(get_env_value(minishell, "?"));
	}
}

void	execute_semicols(t_minishell *minishell, char *o_input)
{
	int	i;
	int	and_or;
	int	status;

	i = 0;
	while (minishell->semicols[i])
	{
		and_or = which_operator(&o_input);
		if (ft_contains("()", *o_input))
		{
			o_input++;
			if ((*(o_input - 1) == '(')
				&& ((and_or == 2 && !status) || (and_or == 1 && status)))
			{
				o_input += skip_block(o_input, &i);
				continue ;
			}
			if (*(o_input - 1) == ')')
				continue ;
		}
		actual_exec_semicols(minishell, i++, and_or, &status);
		o_input += ft_strlen_skipspaces(minishell->input);
		free(minishell->input);
	}
}
