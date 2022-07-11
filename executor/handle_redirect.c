/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonjan <hyeonjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 23:29:52 by hyeonjan          #+#    #+#             */
/*   Updated: 2022/07/11 21:41:24 by hyeonjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	_redir(char *file_name, int flag, int target_fd, int mode)
{
	int	fd;

	if (mode)
		fd = open(file_name, flag, mode);
	else
		fd = open(file_name, flag);
	if (fd == -1)
		return (FAIL);
	if (dup2(fd, target_fd) == -1)
		exit_msg(EXIT_FAILURE, STDERR_FILENO, "dup2 fail\n");
	if (close(fd))
		exit_msg(EXIT_FAILURE, STDERR_FILENO, "close fail\n");
	return (SUCCESS);
}

int	_redir_in(char *file_name)
{
	return (_redir(file_name, O_RDONLY, STDIN_FILENO, 0));
}

int	_redir_out(char *file_name)
{
	return (_redir(file_name, O_WRONLY | O_TRUNC | O_CREAT, \
					STDOUT_FILENO, 0644));
}

int	_redir_append(char *file_name)
{
	return (_redir(file_name, O_WRONLY | O_APPEND | O_CREAT, \
					STDOUT_FILENO, 0644));
}

int	handle_redirect(t_sh *sh, t_command *command)
{
	int		token_size;
	t_token	*token;

	token = command->tokens;
	token_size = command->token_size;
	while (token_size)
	{
		if ((token->type == T_LRDIR && !_redir_in(token->next->str)) || \
			(token->type == T_RRDIR && !_redir_out(token->next->str)) || \
			(token->type == T_APPEND && !_redir_append(token->next->str)) || \
			(token->type == T_HEREDOC && !redir_heredoc(sh)))
			return (FAIL);
		token_size--;
		token = token->next;
	}
	// sh->exit_status = 1;
	return (SUCCESS);
}
