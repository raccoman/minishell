#ifndef MINISHELL_H
#define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <termios.h>
# include "color.h"
# include "../libraries/libft/libft.h"

extern int	errno;

typedef struct	s_minishell
{
	struct termios	our_cfg;
	struct termios	sys_cfg;
	int				running;
	char			**main_env;
	char			*input;
	int				cursor;
}				t_minishell;

typedef enum	e_key
{
	KEY_NONE,
	KEY_ENTER,
	KEY_UP,
	KEY_DOWN,
	KEY_RIGHT,
	KEY_LEFT,
}				t_key;

void	configure(t_minishell *minishell, char *env[]);
void	terminate(t_minishell *minishell);
void	get_input(t_minishell *minishell);
void	parse(t_minishell *minishell);

t_key	get_key(char c);
void	handle_key(t_minishell *minishell, t_key key);

#endif
