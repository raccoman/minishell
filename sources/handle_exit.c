/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordanraccoman <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 13:13:55 by mgiordan          #+#    #+#             */
/*   Updated: 2021/05/24 13:13:56 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	terminate(t_minishell *minishell)
{
	free(minishell->input);
	if (minishell->o_input)
		free(minishell->o_input);
	ft_free2D((void **)minishell->semicols);
	free(minishell->prompt);
	free(minishell->clipboard);
	clear_history(minishell->history);
	clear_commands(minishell->command);
	free(minishell->command);
	ft_lstclear(&minishell->main_env);
	ft_lstclear(&minishell->session_env);
	ft_lstclear(&minishell->exported);
	free(minishell);
}

void	handle_exit(t_minishell *minishell, t_simple_cmd *curr)
{
	char	**args;
	char	*prefix;
	int		exit_value;

	exit_value = ft_atoi(get_env_value(minishell, "?"));
	if (curr && curr->arguments[1])
	{
		args = &(curr->arguments[1]);
		if (!ft_is_num(*args))
		{
			prefix = ft_strjoin("exit: ", *args);
			print_error(prefix, "numeric argument required");
			free(prefix);
			exit_value = 1;
		}
		else
			exit_value = ft_atoi(*args);
	}
	printf(CC_WHT "Bye bye" CC_RESET "\n");
	terminate(minishell);
	exit((exit_value + 256) % 256);
}
