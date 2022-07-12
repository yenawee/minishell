/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_argv_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonjan <hyeonjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 22:44:32 by hyeonjan          #+#    #+#             */
/*   Updated: 2022/07/12 23:11:22 by hyeonjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	*_expand_variable(t_sh *sh, char **ret, char *var)
{
	char	*key;
	char	*malloced_val;
	size_t	i;

	if (*var == '?')
	{
		*ret = var + 1;
		return (ft_alert_itoa(sh->exit_status));
	}
	i = 1;
	while (var[i] == '_' || ft_isalnum(var[i]))
		i++;
	*ret = &var[i];
	key = ft_alert_substr(var, 0, i);
	malloced_val = get_env_value(sh->env_list, key);
	// printf("key: %s\n", key);
	safe_free((void **)&key);
	return (malloced_val);
}

static void	_expand_pusback(t_sh *sh, t_token **argv, char *str)
{
	char	*ret;
	t_token	*new_node;
	t_token	*cur;

	ret = expand_str(str, sh);
	if (*str == '$' && *ret == '\0')
		free(ret);
	else
	{
		new_node = ft_alert_calloc(1, sizeof(t_token));
		new_node->str = ret;
		new_node->type = T_WORD;
		if (*argv == NULL)
			*argv = new_node;
		else
		{
			cur = *argv;
			while (cur->next)
			{
				new_node->prev = cur;
				cur = cur->next;
			}
			cur->next = new_node;
		}
	}
}

static char	*_expand_out_of_quote(t_sh *sh, char *str, char *p, char *ret)
{
	while (42)
	{
		while (*p && !ft_strchr("\'\"$", *p))
			p++;
		if (*p == '\0')
		{
			ft_alert_str_append(&ret, str);
			// printf("ret1: %s\n", ret);
			break ;
		}
		else if (ft_strchr("\'\"", *p))
			p = ft_strchr(p + 1, *p) + 1;
		else if (*p == '$' && !ft_strchr("_?", p[1]) && !ft_isalpha(p[1]))
			p++;
		else if (*p == '$')
		{
			ft_alert_added(&ret, ft_alert_substr(str, 0, p - str));
			ft_alert_added(&ret, _expand_variable(sh, &str, &p[1]));
			// printf("ret2: %s\n", ret);
			p = str;
		}
	}
	return (ret);
}

static void	_add_argv(t_sh *sh, t_token **argv, char *str)
{
	char	*ret;
	char	*p;
	char	*front;

	if (*str == '\0')
		return ;
	ret = _expand_out_of_quote(sh, str, str, NULL);
	if (ret == NULL)
		return ;
	// printf("_expand_out_of_quote: %s\n", ret);
	p = ret;
	while (*p)
	{
		while (*p && ft_strchr(" \t", *p))
			p++;
		if (*p == '\0')
			break ;
		front = p;
		while (*p && !ft_strchr(" \t", *p))
		{
			if (ft_strchr("\'\"", *p))
				p = ft_strchr(p + 1, *p);
			p++;
		}
		if (*p)
			*p++ = '\0';
		_expand_pusback(sh, argv, front);
	}
	safe_free((void **)&ret);
}

void	make_argv_list(t_sh *sh, t_token **argv, t_command *cmd)
{
	t_token	*cur_token;
	int		token_i;

	cur_token = cmd->tokens;
	token_i = 0;
	while (token_i < cmd->token_size)
	{
		if (cur_token->type == T_WORD)
			_add_argv(sh, argv, cur_token->str);
		token_i++;
		cur_token = cur_token->next;
	}
}
