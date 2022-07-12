/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_no_arg.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenawee <yenawee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 22:50:02 by hyeonjan          #+#    #+#             */
/*   Updated: 2022/07/12 12:35:10 by yenawee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	_swap_t_env(t_env **a, t_env **b)
{
	t_env	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

static void	_selection_sort_env_arr(t_env **env_arr)
{
	t_env	**target;
	t_env	**cur;

	while (*env_arr)
	{
		target = env_arr;
		cur = env_arr + 1;
		while (*cur)
		{
			if (ft_strcmp((*target)->key, (*cur)->key) > 0)
				target = cur;
			cur++;
		}
		if (env_arr != target)
			_swap_t_env(env_arr, target);
		env_arr++;
	}
}

static t_env	**_get_t_env_arr_from_t_list(t_list *env_list)
{
	t_env	**ret;
	t_list	*cur;
	size_t	i;

	ret = ft_calloc(ft_lstsize(env_list) + 1, sizeof(t_env *));
	if (ret == NULL)
		return (NULL);
	cur = env_list;
	i = 0;
	while (cur)
	{
		ret[i++] = (t_env *)cur->content;
		cur = cur->next;
	}
	ret[i] = NULL;
	return (ret);
}

static t_env	**_ft_sorted_t_env_from_t_list(t_list *env_list)
{
	t_env	**env_arr;
	t_list	*cur;
	t_list	*candidate;
	size_t	i;

	env_arr = _get_t_env_arr_from_t_list(env_list);
	if (env_arr == NULL)
		return (NULL);
	_selection_sort_env_arr(env_arr);
	return (env_arr);
}

int	ft_export_no_arg(t_list *env_list)
{
	t_env	**ret;
	t_env	**origin;

	ret = _ft_sorted_t_env_from_t_list(env_list);
	if (ret == NULL)
		exit(EXIT_FAILURE);
	origin = ret;
	while (*ret)
	{
		export_print(*ret);
		ret++;
	}
	safe_free((void **)&origin);
	return (EXIT_SUCCESS);
}
