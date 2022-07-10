/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_to_char_array.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenawee <yenawee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 19:38:28 by yenawee           #+#    #+#             */
/*   Updated: 2022/07/10 19:39:33 by yenawee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	env_count(t_list	*env_list)
{
	t_list	*curr;
	int		env_cnt;

	curr = env_list;
	env_cnt = 0;
	while (curr)
	{
		if (((t_env *)(curr->content))->value)
			env_cnt++;
		curr = curr->next;
	}
	return (env_cnt);
}

static char	*get_env_line(t_list *env_list)
{
	char	*ret;
	char	*key;
	char	*value;
	t_env	*env;
	char	*tmp;

	env = (t_env *)env_list->content;
	key = ft_strdup(env->key);
	value = ft_strdup(env->value);
	ret = ft_strjoin(key, "=");
	tmp = ret;
	ret = ft_strjoin(ret, value);
	safe_free(&tmp);
	return (ret);
}

char	**env_list_to_char_arr(t_list *env_list)
{
	char	**env_arr;
	t_list	*curr;
	int		env_cnt;
	int		i;

	curr = env_list;
	env_cnt = env_count(env_list);
	env_arr = ft_alert_calloc(env_cnt + 1, sizeof(char *));
	i = 0;
	while (i < env_cnt)
	{
		if (((t_env *)(curr->content))->value)
			env_arr[i] = get_env_line(curr);
		curr = curr->next;
		i++;
	}
	env_arr[i] = NULL;
	return (env_arr);
}
