/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonjan <hyeonjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 16:37:12 by hyeonjan          #+#    #+#             */
/*   Updated: 2022/07/10 17:39:26 by hyeonjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	_end_prompt(int signal)
{
	(void)signal;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	exit(EXIT_FAILURE);
}

void	_set_heredoc(char **file_name, int *fd, int i)
{
	char				buf[12];
	const char			*alnum = "0123456789abcdef";

	ft_strlcpy(buf, "./heredoc_", 12);
	buf[10] = alnum[i];
	buf[11] = '\0';
	*file_name = ft_alert_strdup(buf);
	*fd = open(*file_name, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (*fd < 0)
		exit_msg(EXIT_FAILURE, STDERR_FILENO, "fail open()\n");
}

void	_read(char **eof, t_list *env_list, int i)
{
	char	*file_name;
	int		fd;
	char	*input;

	input = NULL;
	_set_heredoc(&file_name, &fd, i);
	while (42)
	{
		safe_free((void **)&input);
		input = readline("heredoc 🐚> ");
		if (input == NULL)
			write(1, "\n", 1);
		if (input == NULL || ft_strcmp(input, *eof) == 0)
			break ;
		expand_in_heredoc(input, fd, env_list);
	}
	close(fd);
	safe_free(eof);
	*eof = file_name;
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
		signal(SIGINT, _end_prompt);
		i = 0;
		while (tokens)
		{
			if (tokens->type == T_HEREDOC)
				_read(&tokens->next->str, env_list, i++);
			tokens = tokens->next;
		}
		exit(EXIT_SUCCESS);
	}
	return (wait_child(pid) == 0);
}
