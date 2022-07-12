/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_one.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenawee <yenawee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 19:09:02 by yenawee           #+#    #+#             */
/*   Updated: 2022/07/12 12:35:27 by yenawee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	export_when_key_exist(t_list *curr, char *key, \
char *value, int plus_flag)
{
	t_env	*tmp;
	char	*temp;

	tmp = (t_env *)curr->content;
	if (!ft_strcmp((const char *)tmp->key, (const char *)key))
	{
		if (plus_flag)
		{
			temp = tmp->value;
			tmp->value = ft_strjoin(temp, value);
			safe_free((void **)&temp);
		}
		else
		{
			safe_free((void **)&(tmp->value));
			if (value)
				tmp->value = ft_strdup(value);
			else
				tmp->value = NULL;
		}
		return (SUCCESS);
	}
	return (FAIL);
}

void	ft_export_one(t_list **list, char *key, char *value, int plus_flag)
{
	t_list	*curr;
	t_env	*content;
	t_list	*new_node;

	curr = *list;
	while (curr)
	{
		if (export_when_key_exist(curr, key, value, plus_flag))
			return ;
		curr = curr->next;
	}
	content = ft_alert_calloc(1, sizeof(t_env));
	content->key = ft_strdup(key);
	if (value)
		content->value = ft_strdup(value);
	else
		content->value = NULL;
	new_node = ft_lstnew(content);
	ft_lstadd_back(list, new_node);
}
