#include "headers/minishell.h"

void	prompt(t_minishell *minishell, const char *prefix)
{
	int	length;

	printf("%c[2K", 27);
	//minishell->cursor++;
	printf(CC_RESET "%s", prefix);
	if (minishell->prompt)
		printf("%s", minishell->prompt);
	if (minishell->input)
		printf(CC_CYN "maxishell $> " CC_MAG "%s", minishell->input);
	else
		printf(CC_CYN "maxishell $> " CC_MAG);
	/*if (minishell->input)
		printf(CC_RESET "%s" CC_CYN "maxishell $> " CC_MAG "%s", prefix, minishell->input);
	else
		printf(CC_RESET "%s" CC_CYN "maxishell $> " CC_MAG, prefix);*/
	length = ft_strlen(minishell->input);
	while (minishell->cursor < length--)
		printf("\033[1D");
}

void	watermark()
{
	printf("%c[1;1H%c[2J", 27, 27);
	printf("\n" CC_CYN
		   "███╗   ███╗ █████╗ ██╗  ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     \n"
		   "████╗ ████║██╔══██╗╚██╗██╔╝██║██╔════╝██║  ██║██╔════╝██║     ██║     \n"
		   "██╔████╔██║███████║ ╚███╔╝ ██║███████╗███████║█████╗  ██║     ██║     \n"
		   "██║╚██╔╝██║██╔══██║ ██╔██╗ ██║╚════██║██╔══██║██╔══╝  ██║     ██║     \n"
		   "██║ ╚═╝ ██║██║  ██║██╔╝ ██╗██║███████║██║  ██║███████╗███████╗███████╗\n"
		   "╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n"
		   CC_WHT "Made by " CC_UGRN "raccoman" CC_WHT " and " CC_UGRN "mgiordan" CC_RESET "\n");
}

int	main(int argc, char *argv[], char *env[])
{
	g_minishell = malloc(sizeof(t_minishell));

	(void)argc;
	(void)argv;
	configure(g_minishell, env);
	watermark();
	//prompt(g_minishell, "");
	printf(CC_CYN "maxishell $> " CC_MAG);
	while (g_minishell->running)
	{
		ft_fflush(stdout);
		get_input(g_minishell);
		handle_enter(g_minishell);
	}
	terminate(g_minishell);
	return (0);
}