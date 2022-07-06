/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_to_t_wildcard.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonjan <hyeonjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 22:22:35 by hyeonjan          #+#    #+#             */
/*   Updated: 2022/07/05 22:22:38 by hyeonjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*_set_front_token(t_wildcard *ret, char *str)
{
	if (*str != '*')
	{
		*(ft_strchr(str, '*')) = '\0';
		ret->front_token = str;
		ret->front_token = ft_strdup(str);
		str += ft_strlen(str) + 1;
	}
	return (str);
}

void	_set_rear_token(t_wildcard *ret, char *str)
{
	char	*rear;

	rear = str + ft_strlen(str);
	while (!ft_strchr("*\0", *(rear - 1)))
		--rear;
	if (*rear)
	{
		ret->rear_token = ft_strdup(rear);
		*rear = '\0';
	}
}

void	_set_middle_tokens(t_wildcard *ret, char *str)
{
	t_list		*new_node;

	while (*str)
	{
		while (*str == '*')
			str++;
		if (*str == '\0')
			break ;
		if (ft_strchr(str, '*'))
			*(ft_strchr(str, '*')) = '\0';
		new_node = ft_lstnew((void *)str);
		if (new_node == NULL)
			exit_msg(EXIT_FAILURE, STDERR_FILENO, "malloc error\n");
		ft_lstadd_back(&ret->middle_tokens, new_node);
		str += ft_strlen(str) + 1;
	}
}

t_wildcard	*str_to_t_wildcard(char *str)
{
	t_wildcard	*ret;
	t_list		*node;

	printf("str: |%s|\n", str);
	ret = ft_alert_calloc(1, sizeof(t_wildcard));
	str = _set_front_token(ret, str);
	_set_rear_token(ret, str);
	_set_middle_tokens(ret, str);
	return (ret);
}
