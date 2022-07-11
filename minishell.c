/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonjan <hyeonjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 19:22:38 by hyeonjan          #+#    #+#             */
/*   Updated: 2022/07/11 20:39:21 by hyeonjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

static void	_loop(t_sh *sh, char *input, t_pipeline *list, t_token *tokens)
{
	char		*trimed;

	while (TRUE)
	{
		all_clear(&input, &trimed, &list, &tokens);
		set_input_signal();
		sh->heredoc_index = 0;
		input = readline("🐚 > ");
		if (!input)
			exit_msg(EXIT_SUCCESS, STDOUT_FILENO, "exit\n");
		if (*input)
			add_history(input);
		trimed = ft_strtrim_without_malloc(input, " \t");
		if (*trimed == '\0')
			continue ;
		if (!parse(&tokens, trimed, sh->env_list) || \
			!make_pipelines(&list, tokens) || \
			!handle_heredoc(tokens, sh->env_list))
			sh->exit_status = 1;
		else
			execute_input(sh, list, NULL, 0);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_sh	sh;

	welcome_prompt();
	if (ac != 1)
		printf("No arguments needed!\n");
	sh.fd_stdin = dup(STDIN_FILENO);
	sh.fd_stdout = dup(STDOUT_FILENO);
	sh.fd_stderr = dup(STDERR_FILENO);
	if (sh.fd_stdin == -1 || sh.fd_stdin == -1 || sh.fd_stdin == -1)
		exit_msg(EXIT_FAILURE, STDERR_FILENO, "fail dup()\n");
	sh.env_list = envp_init(envp);
	_loop(&sh, NULL, NULL, NULL);
	return (0);
}
