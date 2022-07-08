/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonjan <hyeonjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 19:22:38 by hyeonjan          #+#    #+#             */
/*   Updated: 2022/07/08 20:24:19 by hyeonjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

static void	loop(char *input, t_sh *sh)
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
		safe_free((void **)&input);
		safe_free((void **)&trimed);
		input = readline(prompt);
		list = NULL;
		tokens = NULL;
		if (!input)
			exit_msg(EXIT_SUCCESS, STDOUT_FILENO, "exit\n");
		if (*input)
			add_history(input);
		trimed = ft_strtrim(input, " \t");
		if (*trimed == '\0')
			continue ;
		if (!parse(&tokens, trimed, sh->env_list) || \
			!make_pipelines(&list, tokens) || \
			!handle_heredoc(tokens, sh->env_list))
		{
			sh->exit_status = 1;
		}
		else
		{
			// test_list(list);`
			execute_input(sh, list);
		}
	}
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_sh	*sh;

	sh = ft_alert_calloc(1, sizeof(t_sh));
	sh->fd_stdin = dup(STDIN_FILENO);
	sh->fd_stdout = dup(STDOUT_FILENO);
	sh->fd_stderr = dup(STDERR_FILENO);
	input = NULL;
	if (ac != 1)
		printf("No arguments needed!\n");
	sh->env_list = envp_init(envp);
	set_input_signal();
	loop(input, sh);
	return (0);
}
