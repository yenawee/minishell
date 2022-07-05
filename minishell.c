#include "./include/minishell.h"

static void	new_prompt(int signal)
{
	(void)signal;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

static void	set_input_signal(void)
{
	// signal(SIGINT, new_prompt);
	signal(SIGQUIT, SIG_IGN);
}

static void	loop(char *input, t_list **env_list)
{
	const char	*prompt = "🐚 > ";
	char		*trimed;
	t_token		*tokens;
	t_pipeline	*list;

	tokens = NULL;
	trimed = NULL;
	list = NULL;
	while (TRUE)
	{
		//clear 함수 구현해야 함
		safe_free((void **)&trimed);
		input = readline(prompt);
		list = NULL;
		tokens = NULL;
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
		if (!make_pipelines(&list, tokens))
			continue ;
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
	set_input_signal();
	loop(input, &env_list);
	return (0);
}
