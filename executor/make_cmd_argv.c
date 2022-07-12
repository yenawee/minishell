/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd_argv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonjan <hyeonjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 20:42:53 by hyeonjan          #+#    #+#             */
/*   Updated: 2022/07/12 20:08:14 by hyeonjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_argc(t_command *cmd)
{
	int			cnt;
	t_token		*cur;
	int			i;

	i = 0;
	cnt = 0;
	cur = cmd->tokens;
	while (i < cmd->token_size)
	{
		if (cur->type == T_WORD)
			cnt++;
		i++;
		cur = cur->next;
	}
	return (cnt);
}

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

void	make_cmd_argv(t_command *cmd, t_sh *sh)
{
	t_token		*cur_token;
	int			i;
	int			token_i;

	cmd->argc = get_argc(cmd);
	cmd->argv = ft_alert_calloc(cmd->argc + 1, sizeof(char *));
	cur_token = cmd->tokens;
	i = 0;
	token_i = 0;
	while (token_i < cmd->token_size)
	{
		if (cur_token->type == T_WORD && \
			_temp_expand_str(&cmd->argv[i], cur_token->str, sh))
			i++;
		token_i++;
		cur_token = cur_token->next;
	}
}
