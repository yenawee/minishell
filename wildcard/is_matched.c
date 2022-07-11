/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_matched.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonjan <hyeonjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 22:19:21 by hyeonjan          #+#    #+#             */
/*   Updated: 2022/07/11 20:55:21 by hyeonjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	_is_str_matched(char *target, char *token)
{
	while (*token)
		if (*target++ != *token++)
			return (FAIL);
	return (SUCCESS);
}

int	_is_front_token_matched(char *file_name, char *front_token)
{
	return (front_token == NULL || _is_str_matched(file_name, front_token));
}

int	_is_rear_token_matched(char *file_name, char *rear_token)
{
	return (rear_token == NULL || \
		ft_strcmp(file_name + ft_strlen(file_name) - ft_strlen(rear_token), \
				rear_token) == 0);
}

int	_is_middle_tokens_matched(char *file_name, t_list *middle_tokens, \
								char *front_token, char *rear_token)
{
	char	*deadline;

	if (front_token)
		file_name += ft_strlen(front_token);
	deadline = file_name + ft_strlen(file_name);
	if (rear_token)
		deadline -= ft_strlen(rear_token);
	while (middle_tokens)
	{
		while (!_is_str_matched(file_name, (char *)middle_tokens->content))
			if (++file_name >= deadline)
				return (FAIL);
		file_name += ft_strlen((const char *)middle_tokens->content);
		middle_tokens = middle_tokens->next;
	}
	return (SUCCESS);
}

int	is_matched(char *file_name, t_wc *wildcard)
{
	return (ft_strlen(file_name) >= wildcard->total_len && \
			_is_front_token_matched(file_name, wildcard->front_token) && \
			_is_rear_token_matched(file_name, wildcard->rear_token) && \
			_is_middle_tokens_matched(file_name, wildcard->middle_tokens, \
								wildcard->front_token, wildcard->rear_token)
	);
}
