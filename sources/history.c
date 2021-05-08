#include "minishell.h"

t_history	*get_last_history(t_history *history)
{
	while (history->next)
		history = history->next;
	return (history);
}

t_history	*get_first_history(t_history *history)
{
	while (history->prec)
		history = history->prec;
	return (history);
}

void	add_history(t_minishell *minishell, char *cmd_line)
{
	t_history	*tmp;
	t_history	*tmp_2;
	t_history	*last;
	
	tmp = malloc(sizeof(t_history));
	tmp->cmd_line = ft_strdup(cmd_line);
	last = get_last_history(minishell->history);
	tmp_2 = last->prec;
	last->prec = tmp;
	tmp->next = last;
	tmp->prec = tmp_2;
	if (tmp_2)
		tmp_2->next = tmp;
	minishell->history = last;
}

void	init_history(t_minishell *minishell)
{
	t_history	*tmp;

	tmp = malloc(sizeof(t_history));
	tmp->cmd_line = ft_strdup("");
	tmp->next = NULL;
	tmp->prec = NULL;
	minishell->history = tmp;	
}

void	clear_history(t_history *history)
{
	t_history	*first;
	t_history	*tmp;

	first = get_first_history(history);
	while (first)
	{
		free(first->cmd_line);
		tmp = first->next;
		free(first);
		first = tmp;
	}
}