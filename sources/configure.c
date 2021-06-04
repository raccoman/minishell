/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configure.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordanraccoman <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 13:12:40 by mgiordan          #+#    #+#             */
/*   Updated: 2021/05/24 13:12:42 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	configure_termios(t_minishell *minishell)
{
	tcgetattr(0, &minishell->sys_cfg);
	ft_memcpy(&minishell->our_cfg, &minishell->sys_cfg, sizeof(struct termios));
	minishell->our_cfg.c_lflag &= ~(ECHO | ICANON);
	minishell->our_cfg.c_cc[VMIN] = 1;
	minishell->our_cfg.c_cc[VTIME] = 0;
}

void	configure_shlvl_term(t_minishell *minishell)
{
	char	*tmp;

	tmp = get_env_value(minishell, "SHLVL");
	if (!tmp)
		single_export(minishell, "SHLVL=1");
	else
	{
		tmp = ft_itoa(ft_atoi(tmp) + 1);
		single_assign(minishell, ft_strjoin("SHLVL=", tmp));
		free(tmp);
	}
	tmp = get_env_value(minishell, "TERM");
	if (!tmp)
		single_assign(minishell, ft_strdup("TERM=dumb"));
}

void	configure_env(t_minishell *minishell, char	**env)
{
	minishell->main_env = NULL;
	while (*env)
	{
		ft_lstadd_back(&minishell->main_env, ft_lstnew(ft_strdup(*env)));
		env++;
	}
	minishell->session_env = NULL;
	configure_shlvl_term(minishell);
	single_assign(minishell, ft_strdup("?=0"));
	minishell->exported = NULL;
}

void	init_history(t_minishell *minishell)
{
	t_history	*tmp;

	tmp = malloc(sizeof(t_history));
	tmp->cmd_line = ft_strdup("");
	tmp->safe = ft_strdup("");
	tmp->next = NULL;
	tmp->prec = NULL;
	minishell->history = tmp;
}

void	configure(t_minishell *minishell, char **env)
{
	configure_env(minishell, env);
	minishell->running = 1;
	init_history(minishell);
	minishell->clipboard = NULL;
	minishell->prompt = NULL;
	minishell->input = NULL;
	minishell->semicols = NULL;
	minishell->cursor = 0;
	minishell->last_len = PROMPT_LEN;
	configure_termios(minishell);
	minishell->command = malloc(sizeof(t_command));
	minishell->command->infile = NULL;
	minishell->command->outfile = NULL;
	minishell->command->append = 0;
	minishell->command->here_doc = 0;
	minishell->command->s_commands = NULL;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	minishell->pid = -1;
}
