/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_in_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonjan <hyeonjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 16:40:09 by hyeonjan          #+#    #+#             */
/*   Updated: 2022/07/12 20:56:38 by hyeonjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*_handle_exit_status(char *s, int fd, int exit_status)
{
	char	*ret;

	ret = ft_itoa(exit_status);
	ft_putstr_fd(fd, ret);
	safe_free((void **)&ret);
	return (s + 1);
}

static char	*_expand_variable(t_sh *sh, char *s, int fd, t_list *env_list)
{
	char	temp;
	char	*var;
	char	*malloced_val;

	if (*s == '?')
		return (_handle_exit_status(s, fd, sh->exit_status));
	if (*s != '_' && !ft_isalpha(*s))
	{
		ft_putstr_fd(fd, "$");
		return (s);
	}
	var = s;
	while (*s == '_' || ft_isalnum(*s))
		s++;
	temp = *s;
	*s = '\0';
	malloced_val = get_env_value(env_list, var);
	*s = temp;
	return (s);
}

void	expand_in_heredoc(t_sh *sh, char *input, int fd, t_list *env_list)
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
		input = _expand_variable(sh, dollar + 1, fd, env_list);
	}
}
