/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd_argv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonjan <hyeonjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 20:42:53 by hyeonjan          #+#    #+#             */
/*   Updated: 2022/07/12 21:49:08 by hyeonjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	_temp_expand_str(char **argv_i, char *str, t_sh *sh)
{
	char	*ret;

	ret = expand_str(str, sh);
	if (*str == '$' && *ret == '\0')
	{
		free(ret);
		return (0);
	}
	*argv_i = ret;
	return (1);
}

void	*_expand_variable(t_sh *sh, char **ret, char *var)
{
	char	*key;
	char	*malloced_val;
	char	*s;

	if (*var == '?')
	{
		*ret = var + 1;
		return (ft_alert_itoa(sh->exit_status));
	}
	s = var;
	while (*s == '_' || ft_isalnum(*s))
		s++;
	*ret = s;
	key = ft_alert_substr(var, 0, (size_t)(s - var));
	malloced_val = get_env_value(sh->env_list, key);
	safe_free((void **)&key);
	return (malloced_val);
}

static char	*_expand_out_of_quote(t_sh *sh, char *str, char *p, char *ret)
{
	while (42)
	{
		while (*p && !ft_strchr("\'\"$", *p))
			p++;
		if (*p == '\0')
			ft_alert_str_append(&ret, str);
		else if (ft_strchr("\'\"", *p))
			p = ft_strchr(p + 1, *p) + 1;
		else if (*p == '$' && !ft_strchr("_?", p[1]) && !ft_isalpha(p[1]))
			p++;
		else if (*p == '$')
		{
			ft_alert_added(&ret, ft_alert_substr(str, 0, p - str));
			ft_alert_added(&ret, _expand_variable(sh, &str, &p[1]));
			p = str;
		}
	}
	return (ret);
}

void	_expand_pusback(t_sh *sh, t_token **argv, char *str)
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

void	_add_argv(t_sh *sh, t_token **argv, char *str)
{
	char	*ret;
	char	**words;
	char	**origin;

	if (*str == '\0')
		return ;
	ret = _expand_out_of_quote(sh, str, str, NULL);
	words = ft_split((const char *)ret, ' ');
	if (words == NULL)
		exit_msg(EXIT_FAILURE, STDERR_FILENO, "fail malloc()\n");
	origin = words;
	while (*words)
	{
		_expand_pusback(sh, argv, *words);
		words++;
	}
}

void	_f(t_command *cmd, t_token *argv)
{
	t_token	*cur;
	t_token	*temp;
	int		i;

	cur = argv;
	while (cur)
	{
		cur = cur->next;
		(cmd->argc)++;
	}
	cmd->argv = ft_alert_calloc(cmd->argc + 1, sizeof(char *));
	cur = argv;
	i = 0;
	while (cur)
	{
		cmd->argv[i++] = cur->str;
		temp = cur;
		cur = cur->next;
		free(temp);
	}
}

void	make_cmd_argv(t_command *cmd, t_sh *sh)
{
	t_token	*argv;
	t_token	*cur_token;
	int		token_i;

	cur_token = cmd->tokens;
	token_i = 0;
	argv = NULL;
	while (token_i < cmd->token_size)
	{
		if (cur_token->type == T_WORD)
			_add_argv(sh, &argv, cur_token->str);
		token_i++;
		cur_token = cur_token->next;
	}
	_f(cmd, argv);
}
