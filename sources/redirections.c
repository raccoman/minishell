#include "minishell.h"

int	handle_here_doc(char *delim, int single)
{
	char	*buffer;
	char	*safe;
	char	c;
	t_key	key;
	int		fdpipe[2];

	pipe(fdpipe);
	g_minishell->quotes.done = 0;
	g_minishell->pid = fork();
	if (!g_minishell->pid)
	{
		buffer = malloc(1);
		*buffer = 0;
		free(g_minishell->input);
		g_minishell->input = ft_strdup("");
		prompt(g_minishell, "");
		g_minishell->cursor = 0;
		while (1)
		{
			ft_fflush(stdout);
			tcsetattr(0, TCSANOW, &g_minishell->our_cfg);
			read(0, &c, 1);
			key = get_key(c);
			tcsetattr(0, TCSANOW, &g_minishell->sys_cfg);
			if (key == KEY_EOF)
			{
				if (!g_minishell->input || !*g_minishell->input)
				{
					printf("\n");
					break ;
				}
				printf("\a");
				continue ;
			}
			if (key == KEY_ENTER)
			{
				printf("\n");
				if (!ft_strcmp(g_minishell->input, delim))
					break ;
				safe = g_minishell->input;
				g_minishell->input = ft_strjoin(g_minishell->input, "\n");
				free(safe);
				safe = buffer;
				buffer = ft_strjoin(buffer, g_minishell->input);
				free(safe);
				free(g_minishell->input);
				g_minishell->input = ft_strdup("");
				prompt(g_minishell, "");
				g_minishell->cursor = 0;
			}
			else if (key != KEY_ALPHANUMERIC)
				handle_key(g_minishell, key);
			else
			{
				g_minishell->input = ft_insert(g_minishell->input, c, g_minishell->cursor);
				update_history(g_minishell->history, g_minishell->input);
				g_minishell->cursor++;
				prompt(g_minishell, "\r"); // il prompt dovrebbe essere '>' o 'heredoc >'
			}
		}
		ft_fflush(stdout);
		write(fdpipe[1], buffer, ft_strlen(buffer));
		free(buffer);
		exit(0);
	}
	waitpid(g_minishell->pid, NULL, 0);
	close(fdpipe[1]);
	printf(CC_RESET);
	ft_fflush(stdout);
	if (single)
	{
		dup2(*fdpipe, 0);
		close(*fdpipe);
	}
	g_minishell->quotes.done = 1;
	return (*fdpipe);
}

int	redirect_infile(char *infile, int tmpin, int here_doc, int single)
{
	int	fdin;

	if (here_doc)
		return (handle_here_doc(infile, single));
	if (infile)
		fdin = open(infile, O_RDONLY);
	else
		fdin = dup(tmpin);
	if (single)
	{
		dup2(fdin, 0);
		close(fdin);
	}
	return (fdin);
}

void	redirect_outfile(char *outfile, int tmpout, int append)
{
	int	fdout;

	if (outfile)
	{
		if (append)
			fdout = open(outfile, O_WRONLY | O_APPEND);
		else
			fdout = open(outfile, O_WRONLY);
	}
	else
		fdout = dup(tmpout);
	dup2(fdout, 1);
	close(fdout);
}

void	restore_stds(int *tmp_stds)
{
	dup2(tmp_stds[0], 0);
	dup2(tmp_stds[1], 1);
	close(tmp_stds[0]);
	close(tmp_stds[1]);
}