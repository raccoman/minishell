#ifndef MINISHELL_H
#define MINISHELL_H

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

# include "color.h"
# include "../libraries/libft/libft.h"

extern int errno;

typedef struct	s_history
{
	char				*cmd_line;
	struct s_history	*prec;
	struct s_history	*next;
}						t_history;

typedef	struct	s_simple_cmd
{
	char	**arguments; // arguments[0] é il comando in se
	struct s_simple_cmd	*next;
}			t_simple_cmd;

typedef struct	s_command
{
	char			*infile;
	char			*outfile;
	int				append;
	t_simple_cmd	*s_commands;
}	t_command;

typedef struct	s_minishell
{
	struct termios	our_cfg;
	struct termios	sys_cfg;
	int				running;
	t_list			*main_env;
	t_list			*session_env;
	char			*input;
	char			*clipboard;
	char			*prompt;
	int				cursor;
	t_history		*history;
	t_command		*command;
	pid_t			pid;
}				t_minishell;

typedef enum	e_key
{
	KEY_UNKNOWN,
	KEY_ALPHANUMERIC,
	KEY_EOF,
	KEY_SHIFT_LEFT,
	KEY_SHIFT_RIGHT,
	KEY_CTRL_UP,
	KEY_CTRL_DOWN,
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
	KEY_END,
}				t_key;

t_minishell	*g_minishell;

void	configure(t_minishell *minishell, char *env[]);
void	terminate(t_minishell *minishell);
void	get_input(t_minishell *minishell);

void	print_error(char *formatted, char *arg);
short	is_option(char *str);
int is_path(char *str);

void	prompt(t_minishell *minishell, const char *prefix);
void	parse_input(t_minishell *minishell);
int		builtins(char *name, t_simple_cmd *curr, t_minishell *minishell);
void    executor(t_minishell *minishell, t_command *command);
void	execute_non_builtin(t_simple_cmd *cmd, t_minishell *minishell);
void	expander(t_minishell *minishell, t_simple_cmd *curr);

t_key	get_key(char c);
void	handle_key(t_minishell *minishell, t_key key);
void	handle_enter(t_minishell *minishell);

void	clear_history(t_history *history);
void	init_history(t_minishell *minishell);
void	add_history(t_minishell *minishell, char *cmd_line);

void	add_command(t_command *command, t_simple_cmd *s_cmd);
int		calc_token_len(char *str);
void	add_argument(t_simple_cmd *s_cmd, char *new_arg);
void	clear_commands(t_command *command);

t_list	*find_env(t_list *env, char *name);
int		is_assign(const char *str);
int		cmd_cmp(char *s1, char *s2);
char	*get_env_value(t_minishell *minishell, char *name);
char	**get_env_matrix(t_list *env);

void	restore_stds(int *tmp_stds);
void	redirect_outfile(char *outfile, int tmpout, int append);
int		redirect_infile(char *infile, int tmpin, int single);

void    handle_exit(t_minishell *minishell);
void    handle_pwd(t_simple_cmd *curr);
void	handle_echo(t_minishell *minishell, t_simple_cmd *curr);
void	handle_env(t_minishell *minishell);
void	handle_assign(t_minishell *minishell, t_simple_cmd *curr);
void	single_assign(t_minishell *minishell, char *assign);
void	handle_export(t_minishell *minishell, t_simple_cmd *curr);
void	handle_cd(t_minishell *minishell, t_simple_cmd *curr);
void	single_export(t_minishell *minishell, char *export);
void	handle_unset(t_minishell *minishell, t_simple_cmd *curr);


#endif
