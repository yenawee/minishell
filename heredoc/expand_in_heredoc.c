/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_in_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonjan <hyeonjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 16:40:09 by hyeonjan          #+#    #+#             */
/*   Updated: 2022/07/10 20:18:20 by hyeonjan         ###   ########.fr       */
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

char	*_expand_variable(char *s, int fd, t_list *env_list)
{
	char	temp;
	char	*var;
	char	*val;

	val = NULL;
	if (*s != '_' && !ft_isalpha(*s))
	{
		ft_putstr_fd(fd, "$");
		return (s);
	}
	var = s++;
	while (*s != '_' && !ft_isalnum(*s))
		s++;
	temp = *s;
	*s = '\0';
	val = _get_env_value_without_malloc(env_list, var);
	if (val)
		ft_putstr_fd(fd, val);
	*s = temp;
	return (s);
}

char	*expand_in_heredoc(char *input, int fd, t_list *env_list)
{
	char	*dollar;

	while (*input)
	{
		dollar = ft_strchr(input, '$');
		if (dollar == NULL)
		{
			ft_putstr_fd(fd, input);
			break ;
		}
		*dollar = '\0';
		ft_putstr_fd(fd, input);
		input = _expand_variable(dollar + 1, fd, env_list);
	}
}
