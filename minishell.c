#include "./include/minishell.h"

static void	new_prompt(int signal)
{
	(void)signal;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

static void	set_signal(void)
{
	// signal(SIGINT, new_prompt);
	signal(SIGQUIT, SIG_IGN);
}

static void	loop(char *input, t_list **env_list)
{
	const char	*prompt = "🐚 > ";
	char		*trimed;
	t_token		*tokens;

	tokens = NULL;
	trimed = NULL;
	while (TRUE)
	{
		safe_free((void **)&trimed);
		input = readline(prompt);
		if (!input)
			exit_msg(EXIT_SUCCESS, STDOUT_FILENO, "exit\n");
		if (*input)
			add_history(input);
		trimed = ft_strtrim(input, " \t");
		safe_free((void **)&input);
		if (*trimed == '\0')
			continue ;
		if (!parse(&tokens, trimed, *env_list))
			continue ;
		// while (tokens)
		// {
		// 	printf("type : %d, str : %s\n", tokens->type, tokens->str);
		// 	tokens = tokens->next;
		// }
	}
}

int main(int ac, char **av, char **envp)
{
	char	*input;
	t_list	*env_list;

	input = NULL;
	if (ac != 1)
		printf("No arguments needed!\n");
	env_list = envp_init(envp);
	set_signal();
	loop(input, &env_list);
	return (0);
}