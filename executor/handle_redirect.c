/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonjan <hyeonjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 23:29:52 by hyeonjan          #+#    #+#             */
/*   Updated: 2022/07/10 18:08:00 by hyeonjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handle_redirect(t_sh *sh, t_command *command)
{
	int		token_size;
	t_token	*token;

	token = command->tokens;
	token_size = command->token_size;
	while (token_size)
	{
		if ((token->type == T_LRDIR && !redir_in(token->next->str)) || \
			(token->type == T_RRDIR && !redir_out(token->next->str)) || \
			(token->type == T_APPEND && !redir_append(token->next->str)) || \
			(token->type == T_HEREDOC && !redir_heredoc(sh)))
			return (FAIL);
		token_size--;
		token = token->next;
	}
	sh->exit_status = 1;
	return (SUCCESS);
}
