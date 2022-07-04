/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_no_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywee <ywee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 22:50:02 by hyeonjan          #+#    #+#             */
/*   Updated: 2022/07/04 19:52:27 by ywee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	_swap_t_env(t_env **a, t_env **b)
{
	t_env	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	_selection_sort_env_arr(t_env **env_arr)
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

t_env	**_get_t_env_arr_from_t_list(t_list *env_list)
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

t_env	**_ft_sorted_t_env_from_t_list(t_list *env_list)
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

void	ft_export_no_arg(t_list *env_list)
{
	t_env	**ret;
	t_env	**origin;

	ret = _ft_sorted_t_env_from_t_list(env_list);
	if (ret == NULL)
		exit(EXIT_FAILURE);
	origin = ret;
	while (*ret)
	{
		if ((*ret)->value)
			printf("declare -x %s=\"%s\"\n", (*ret)->key, (*ret)->value);
		else
			printf("declare -x %s\n", (*ret)->key);
		ret++;
	}
	free(origin);
}

// int	main(int ac, char **av, char **envp)
// {
// 	t_list	*env_list;
// 	t_env	**sorted_t_env_arr;
// 	t_env	**arr;

// 	env_list = envp_init(envp);
// 	if (env_list == NULL)
// 		exit(EXIT_FAILURE);
// 	ft_export_no_arg(env_list);
// 	free(env_list);
// }
