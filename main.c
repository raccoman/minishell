#include "headers/minishell.h"

void	watermark()
{
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
	t_minishell	minishell;

	(void)argc;
	(void)argv;
	configure(&minishell, env);
	watermark();
	printf(CC_CYN "maxishell $> " CC_MAG);
	while (minishell.running)
	{
		ft_fflush(stdout);
		tcsetattr(0, TCSAFLUSH, &minishell.our_cfg);
		get_input(&minishell);
		tcsetattr(0, TCSAFLUSH, &minishell.sys_cfg);
	}
	terminate(&minishell);
	return (0);
}