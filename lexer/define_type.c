/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenawee <yenawee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 19:40:43 by yenawee           #+#    #+#             */
/*   Updated: 2022/07/10 20:04:57 by yenawee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	_define_type(t_token *curr)
{
	if (!ft_strcmp(curr->str, "|"))
		curr->type = T_PIPE;
	else if (!ft_strcmp(curr->str, ">"))
		curr->type = T_RRDIR;
	else if (!ft_strcmp(curr->str, "<"))
		curr->type = T_LRDIR;
	else if (!ft_strcmp(curr->str, "<<"))
		curr->type = T_HEREDOC;
	else if (!ft_strcmp(curr->str, ">>"))
		curr->type = T_APPEND;
	else if (!ft_strcmp(curr->str, "||"))
		curr->type = T_OR;
	else if (!ft_strcmp(curr->str, "&&"))
		curr->type = T_AND;
	else if (curr->prev && (curr->prev->type == T_RRDIR \
	|| curr->prev->type == T_LRDIR || curr->prev->type == T_APPEND))
		curr->type = T_FILE;
	else if (curr->prev && curr->prev->type == T_HEREDOC)
		curr->type = T_LIMITER;
	else
		curr->type = T_WORD;
}

t_token	*define_type(t_token *list)
{
	t_token	*curr;

	curr = list;
	while (curr)
	{
		_define_type(curr);
		curr = curr->next;
	}
	return (list);
}
