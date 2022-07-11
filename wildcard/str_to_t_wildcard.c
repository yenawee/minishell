/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_to_t_wildcard.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonjan <hyeonjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 22:22:35 by hyeonjan          #+#    #+#             */
/*   Updated: 2022/07/11 20:55:34 by hyeonjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*_set_front_token(t_wc *ret, char *str)
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

void	_set_rear_token(t_wc *ret, char *str)
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

void	_set_middle_tokens(t_wc *ret, char *str)
{
	while (*str)
	{
		while (*str == '*')
			str++;
		if (*str == '\0')
			break ;
		if (ft_strchr(str, '*'))
			*(ft_strchr(str, '*')) = '\0';
		ft_lstadd_back(&ret->middle_tokens, ft_alert_lstnew((void *)str));
		str += ft_strlen(str) + 1;
	}
}

t_wc	*str_to_t_wc(char *str)
{
	t_wc	*ret;
	t_list	*node;

	ret = ft_alert_calloc(1, sizeof(t_wc));
	str = _set_front_token(ret, str);
	_set_rear_token(ret, str);
	_set_middle_tokens(ret, str);
	return (ret);
}
