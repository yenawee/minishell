/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd_argv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonjan <hyeonjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 20:42:53 by hyeonjan          #+#    #+#             */
/*   Updated: 2022/07/13 20:23:40 by hyeonjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	_clear_argv(t_token *argv)
{
	t_token	*cur;
	t_token	*temp;

	cur = argv;
	while (cur)
	{
		temp = cur->next;
		free(cur);
		cur = temp;
	}
}

static void	_make_argv_from_argv(t_command *cmd, t_token *argv)
{
	t_token	*cur;
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
		cur = cur->next;
	}
}

void	make_cmd_argv(t_command *cmd, t_sh *sh)
{
	t_token	*argv;

	argv = NULL;
	make_argv_list(sh, &argv, cmd);
	_make_argv_from_argv(cmd, argv);
	_clear_argv(argv);
}
