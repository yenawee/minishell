/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonjan <hyeonjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 19:22:00 by yenawee           #+#    #+#             */
/*   Updated: 2022/07/14 20:26:13 by hyeonjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*_get_env_value_without_malloc(t_list *env_list, char *key)
{
	t_list	*curr;

	curr = env_list;
	while (curr)
	{
		if (!ft_strcmp(((t_env *)curr->content)->key, key))
			return (((t_env *)curr->content)->value);
		curr = curr->next;
	}
	return (NULL);
}

char	*get_env_value(t_list *env_list, char *key)
{
	t_list	*curr;

	curr = env_list;
	while (curr)
	{
		if (!ft_strcmp(((t_env *)curr->content)->key, key))
		{
			if (((t_env *)curr->content)->value)
				return (ft_alert_strdup(((t_env *)curr->content)->value));
			return (NULL);
		}
		curr = curr->next;
	}
	return (NULL);
}
