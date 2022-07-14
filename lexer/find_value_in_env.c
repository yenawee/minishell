/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_value_in_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonjan <hyeonjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 19:41:01 by yenawee           #+#    #+#             */
/*   Updated: 2022/07/14 12:29:06 by hyeonjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*find_value_in_env(char *key, t_list *env_list)
{
	char	*s;
	t_list	*cur;

	cur = env_list;
	while (cur)
	{
		s = ((t_env *)cur->content)->key;
		if (ft_strcmp(s, key) == 0)
		{
			if (((t_env *)cur->content)->value)
				return (((t_env *)cur->content)->value);
			return ("");
		}
		cur = cur->next;
	}
	return ("");
}
