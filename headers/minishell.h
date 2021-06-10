/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordanraccoman <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 13:25:23 by mgiordan          #+#    #+#             */
/*   Updated: 2021/05/24 13:25:27 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <termios.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <limits.h>
# include <string.h>
# include <signal.h>
# include <unistd.h>
# include <errno.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <math.h>

# include "color.h"
# include "libft.h"

# define PROMPT_LEN 13

typedef struct s_history
{
	char				*cmd_line;
	char				*safe;
	struct s_history	*prec;
	struct s_history	*next;
}	t_history;

typedef struct s_simple_cmd
{
	char				**arguments;
	struct s_simple_cmd	*next;
}	t_simple_cmd;

typedef struct s_command
{
	char			*infile;
	char			*outfile;
	int				append;
	int				here_doc;
	t_simple_cmd	*s_commands;
}	t_command;

typedef struct s_minishell
{
	struct termios	our_cfg;
	struct termios	sys_cfg;
	int				running;
	t_list			*main_env;
	t_list			*session_env;
	t_list			*exported;
	char			*input;
	char			*o_input;
	char			**semicols;
	char			*clipboard;
	char			*prompt;
	int				cursor;
	float			last_len;
	t_history		*history;
	t_command		*command;
	pid_t			pid;
}	t_minishell;

typedef enum e_key
{
	KEY_UNKNOWN,
	KEY_ALPHANUMERIC,
	KEY_EOF,
	KEY_SHIFT_LEFT,
	KEY_SHIFT_RIGHT,
	KEY_SHIFT_UP,
	KEY_SHIFT_DOWN,
	KEY_CTRL_X,
	KEY_CTRL_P,
	KEY_CTRL_U,
	KEY_ENTER,
	KEY_TAB,
	KEY_UP,
	KEY_DOWN,
	KEY_RIGHT,
	KEY_LEFT,
	KEY_CANCEL,
	KEY_HOME,
	KEY_END
}	t_key;

typedef enum e_builtin
{
	BUILTIN_ECHO,
	BUILTIN_EXIT,
	BUILTIN_PWD,
	BUILTIN_ENV,
	BUILTIN_EXPORT,
	BUILTIN_CD,
	BUILTIN_UNSET,
	BUILTIN_ASSIGN,
	NONE
}	t_builtin;

t_minishell	*g_minishell;

void	configure(t_minishell *minishell, char *env[]);
void	terminate(t_minishell *minishell);
void	prompt(t_minishell *minishell, const char *prefix);

void	parse_input(t_minishell *minishell);
void	get_input(t_minishell *minishell);
t_key	read_wrapper(t_minishell *minishell, char *c);
void	update_input(t_minishell *minishell, char c);
char	*get_next_token(char **input);

void	expander(t_minishell *minishell, t_simple_cmd *curr);
char	*expand_dquote(t_minishell *minishell, char *token, int *i);
char	*expand_quote(char *token, int *i);
char	*expand_var(t_minishell *minishell, char *token, int *i);

int		builtins(char *name, t_simple_cmd *curr, t_minishell *minishell);
void	executor(t_minishell *minishell, t_command *command);
void	execute_non_builtin(t_simple_cmd *cmd, t_minishell *minishell);
void	execute_pipeline(t_minishell *minishell,
			t_command *command, int *tmp_stds);

int		handle_eof(t_minishell *minishell, t_key key);
char	*update_buffer(t_minishell *minishell, char *buffer);
void	reset_input(t_minishell *minishell);

void	clear_history(t_history *history);
void	init_history(t_minishell *minishell);
void	add_history(t_minishell *minishell, char *cmd_line);
void	update_history(t_history *history, char *new_line);

void	add_command(t_command *command, t_simple_cmd *s_cmd);
void	clear_commands(t_command *command);

t_list	*find_env(t_list *env, char *name);
char	*env_name(const char *env);
char	*get_env_value(t_minishell *minishell, char *name);
char	**lst_to_matrix(t_list *env);
void	set_statusenv(t_minishell *minishell, int code);

void	restore_stds(int *tmp_stds);
void	redirect_outfile(char *outfile, int tmpout, int append);
int		redirect_infile(char *infile, int tmpin, int here_doc, int single);

void	handle_exit(t_minishell *minishell, t_simple_cmd *curr);
void	handle_pwd(t_simple_cmd *curr);
void	handle_echo(t_minishell *minishell, t_simple_cmd *curr);
void	handle_env(t_minishell *minishell, t_simple_cmd *curr);
void	handle_assign(t_minishell *minishell, t_simple_cmd *curr);
void	single_assign(t_minishell *minishell, char *assign);
void	handle_export(t_minishell *minishell, t_simple_cmd *curr);
void	handle_cd(t_minishell *minishell, t_simple_cmd *curr);
void	single_export(t_minishell *minishell, char *export);
void	handle_unset(t_minishell *minishell, t_simple_cmd *curr);

void	handle_sigquit(int signal);
void	handle_sigint(int signal);

t_key	get_key(char c);
void	handle_key(t_minishell *minishell, t_key key);
void	handle_enter(t_minishell *minishell);
void	left_right(t_minishell *sh, t_key key);
void	eof_home_end(t_minishell *sh, t_key key);
void	copy_paste(t_minishell *sh, t_key key);
void	up_down(t_minishell *sh, t_key key);
void	execute_semicols(t_minishell *minishell, char *o_input);

int		first_check(t_minishell *minishell, char *input);
void	adjust_prompt(t_minishell *minishell);
void	print_error(char *prefix, char *error_msg);
int		is_assign(const char *str);
int		is_path(char *str);
short	check_option(char *cmd, char *first);
int		check_quote(char *str);
int		cmd_cmp(char *s1, char *s2);
int		check_file(t_minishell *minishell, char **input, char *error_msg);
char	**safe_split(char *input, char del);

char	*parse_wildcards(char *input);
int		adjust_root(char **root);

void	parse_priorities(t_minishell *sh);
#endif
