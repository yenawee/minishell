/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenawee <yenawee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 19:22:00 by yenawee           #+#    #+#             */
/*   Updated: 2022/07/10 19:39:23 by yenawee          ###   ########.fr       */
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
			return (ft_strdup(((t_env *)curr->content)->value));
		curr = curr->next;
	}
	return (NULL);
}
