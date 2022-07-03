#include "test.h"

void	new_prompt(int signal)
{
	(void)signal;

	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}


// int main()
// {
// 	char	*line_read;
// 	char	*prompt = "🐚 > ";
// 	rl_catch_signals = 0;

// 	while (TRUE)
// 	{
// 		signal(SIGINT, new_prompt);
// 		signal(SIGQUIT, SIG_IGN);
// 		line_read = readline(prompt);
// 		if (line_read && *line_read)
// 			add_history(line_read);
// 		if (!line_read)
// 		{
// 			printf("exit\n");
// 			exit(1);
// 		}
// 	}
// 	return (0);
// }
