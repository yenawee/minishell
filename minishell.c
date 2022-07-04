#include "minishell.h"

void	loop(char *input, t_list **env_list)
{
	char	*prompt = "🐚 > ";

	while (TRUE)
	{
		safe_free(&input);
		input = readline(prompt);
		if (!input)
			exit_msg(EXIT_SUCCESS, STDOUT_FILENO, "exit\n");
		if (*input)
			add_history(input);
	}
}




int main(int ac, char **av, char **envp)
{
	char	*input;
	t_list	*env_list;

	input = NULL;
	if (ac != 1)
		printf("No argument need.\n");
	env_list = envp_init(envp);
	loop(input, &env_list);
	return (0);
}
