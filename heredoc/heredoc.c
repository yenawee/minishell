/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonjan <hyeonjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 16:37:12 by hyeonjan          #+#    #+#             */
/*   Updated: 2022/07/11 21:53:54 by hyeonjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	_set_heredoc(int *fd, int i)
{
	char		file_name[12];
	const char	*alnum = "0123456789abcdef";

	ft_strlcpy(file_name, "./heredoc_", 12);
	file_name[10] = alnum[i];
	file_name[11] = '\0';
	*fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (*fd < 0)
		exit_msg(EXIT_FAILURE, STDERR_FILENO, "fail open()\n");
}

void	_read(char *eof, t_list *env_list, int i)
{
	int		fd;
	char	*input;

	input = NULL;
	_set_heredoc(&fd, i);
	while (42)
	{
		safe_free((void **)&input);
		input = readline("heredoc 🐚> ");
		if (input == NULL)
			write(1, "\n", 1);
		if (input == NULL || ft_strcmp(input, eof) == 0)
			break ;
		ft_putstr_fd(fd, input);
		ft_putstr_fd(fd, "\n");
	}
	close(fd);
	safe_free((void **)&input);
}

int	_is_over_max_heredoc(t_token *tokens)
{
	t_token	*cur;
	int		cnt;

	cnt = 0;
	cur = tokens;
	while (cur)
	{
		if (cur->type == T_HEREDOC && ++cnt > MAX_HEREDOC)
			return (FAIL);
		cur = cur->next;
	}
	return (SUCCESS);
}

int	handle_heredoc(t_token *tokens, t_list *env_list)
{
	int		i;
	pid_t	pid;

	if (!_is_over_max_heredoc(tokens))
	{
		ft_putstr_fd(STDERR_FILENO, "🐚: maximum here-document count exceeded\n");
		return (FAIL);
	}
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		exit_msg(10, STDERR_FILENO, "fail fork()\n");
	else if (pid == 0)
	{
		signal(SIGINT, heredoc_prompt);
		i = 0;
		while (tokens)
		{
			if (tokens->type == T_HEREDOC)
				_read(tokens->next->str, env_list, i++);
			tokens = tokens->next;
		}
		exit(EXIT_SUCCESS);
	}
	return (wait_child(pid) == 0);
}
