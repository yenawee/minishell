/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_argv_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonjan <hyeonjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 22:44:32 by hyeonjan          #+#    #+#             */
/*   Updated: 2022/07/13 21:31:22 by hyeonjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	_expand_pusback(t_sh *sh, t_token **argv, char *str)
{
	char	*ret;
	t_token	*new_node;
	t_token	*cur;

	ret = expand_str(str, sh);
	new_node = ft_alert_calloc(1, sizeof(t_token));
	new_node->str = ret;
	new_node->type = T_WORD;
	if (*argv == NULL)
		*argv = new_node;
	else
	{
		cur = *argv;
		while (cur->next)
			cur = cur->next;
		cur->next = new_node;
		new_node->prev = cur;
	}
}

static void	_add_argv(t_sh *sh, t_token **argv, char *token_str, char *ret)
{
	char	*p;
	char	*front;

	ret = expand_out_of_quote(sh, token_str, token_str, NULL);
	if (ret == NULL)
		return ;
	p = ret;
	while (*p)
	{
		while (*p && ft_strchr(" \t", *p))
			p++;
		if (*p == '\0')
			break ;
		front = p;
		while (*p && !ft_strchr(" \t", *p))
		{
			if (ft_strchr("\'\"", *p))
				p = ft_strchr(p + 1, *p);
			p++;
		}
		if (*p)
			*p++ = '\0';
		_expand_pusback(sh, argv, front);
	}
	safe_free((void **)&ret);
}

void	make_argv_list(t_sh *sh, t_token **argv, t_command *cmd)
{
	t_token	*cur_token;
	int		token_i;

	cur_token = cmd->tokens;
	token_i = 0;
	while (token_i < cmd->token_size)
	{
		if (cur_token->type == T_WORD && *(cur_token->str) == '\0')
			_expand_pusback(sh, argv, cur_token->str);
		else if (cur_token->type == T_WORD)
			_add_argv(sh, argv, cur_token->str, NULL);
		token_i++;
		cur_token = cur_token->next;
	}
}
