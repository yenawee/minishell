/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonjan <hyeonjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 19:38:05 by yenawee           #+#    #+#             */
/*   Updated: 2022/07/14 09:40:54 by hyeonjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_list	*envp_init(char **envp)
{
	t_list	*env_list;
	t_list	*new_node;
	t_env	*content;
	char	*s;

	env_list = NULL;
	while (*envp)
	{
		s = ft_strchr(*envp, '=');
		*s = '\0';
		content = ft_alert_calloc(1, sizeof(t_env));
		content->key = ft_alert_strdup(*envp);
		content->value = ft_alert_strdup(s + 1);
		new_node = ft_lstnew(content);
		ft_lstadd_back(&env_list, new_node);
		envp++;
	}
	return (env_list);
}
