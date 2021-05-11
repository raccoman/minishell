#include "minishell.h"

int	redirect_infile(char *infile, int tmpin, int single)
{
	int	fdin;

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