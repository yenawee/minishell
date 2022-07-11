/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonjan <hyeonjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 22:02:28 by hyeonjan          #+#    #+#             */
/*   Updated: 2022/07/11 20:53:36 by hyeonjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	_clear_commands(t_command **commands)
{
	t_command	*cur;
	t_command	*temp;

	cur = *commands;
	while (cur)
	{
		if (cur->argv)
		{
			two_dim_arr_clear(cur->argv);
			cur->argv = NULL;
		}
		temp = cur->next;
		free(cur);
		cur = temp;
	}
	*commands = NULL;
}

static void	_clear_list(t_pipeline **list)
{
	t_pipeline	*cur;
	t_pipeline	*temp;

	cur = *list;
	while (cur)
	{
		_clear_commands(&cur->commands);
		temp = cur->next;
		free(cur);
		cur = temp;
	}
	*list = NULL;
}

static void	_clear_token(t_token **token)
{
	if (*token)
	{
		if ((*token)->str)
			safe_free((void **)&(*token)->str);
		free(*token);
		*token = NULL;
	}
}

static void	_clear_tokens(t_token **tokens)
{
	t_token	*cur;
	t_token	*temp;

	cur = *tokens;
	while (cur)
	{
		temp = cur->next;
		_clear_token(&cur);
		cur = temp;
	}
	*tokens = NULL;
}

void	all_clear(char **input, char **trimed, \
				t_pipeline **list, t_token **tokens)
{
	t_pipeline	*cur_p;
	t_pipeline	*temp_p;
	t_command	*cur_c;
	t_token		*temp_c;

	safe_free((void **)input);
	*trimed = NULL;
	_clear_list(list);
	_clear_tokens(tokens);
}
