/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywee <ywee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 21:59:37 by hyeonjan          #+#    #+#             */
/*   Updated: 2022/07/11 17:38:20 by ywee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	_restore_fd(t_sh *sh)
{
	ft_alert_safe_dup2(sh, sh->fd_stdin, STDIN_FILENO);
	ft_alert_safe_dup2(sh, sh->fd_stdout, STDOUT_FILENO);
	ft_alert_safe_dup2(sh, sh->fd_stderr, STDERR_FILENO);
}

/**
 * @brief pipeline이 하나의 command만을 보유한 상태.
 *
 * @param env_list
 * @param pipeline
 * @return int exit_status
 */
static int	_execute_single_cmd(t_sh *sh, t_command *command, char **envp)
{
	pid_t	pid;

	if (!handle_redirect(sh, command))
		return (1);
	make_cmd_argv(command, sh);
	if (command->argv[0] == NULL)
		return (0);
	if (is_builtin(command))
		return (execute_builtin(sh, command));
	command->pid = fork();
	if (command->pid == -1)
		exit_msg(10, STDERR_FILENO, "fork error\n");
	else if (command->pid == 0)
	{
		exec_signals();
		execute_simple_cmd(sh, command, envp);
	}
	return (wait_child(command->pid));
}

void	execute_input(t_sh *sh, t_pipeline *list)
{
	char		**envp;
	t_pipeline	*pipeline_node;
	int			prev_sep;

	envp = NULL;
	pipeline_node = list;
	prev_sep = 0;
	_restore_fd(sh);
	while (pipeline_node)
	{
		if ((prev_sep == 0) || (sh->exit_status == 0 && prev_sep == T_AND) || \
			(sh->exit_status != 0 && prev_sep == T_OR))
		{
			envp = env_list_to_char_arr(sh->env_list);
			if (pipeline_node->commands->next == NULL)
				sh->exit_status = _execute_single_cmd(sh, \
									pipeline_node->commands, envp);
			else
				sh->exit_status = execute_pipeline(sh, pipeline_node, envp);
			_restore_fd(sh);
			two_dim_arr_clear(envp);
			envp = NULL ;
		}
		prev_sep = pipeline_node->seperated_type;
		pipeline_node = pipeline_node->next;
	}
}
