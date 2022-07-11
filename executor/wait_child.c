/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywee <ywee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 21:54:59 by hyeonjan          #+#    #+#             */
/*   Updated: 2022/07/11 18:23:53 by ywee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	_trans_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			ft_putstr_fd(STDOUT_FILENO, "\n");
		if (WTERMSIG(status) == SIGQUIT)
			ft_putstr_fd(STDOUT_FILENO, "Quit: 3\n");
		return (WTERMSIG(status));
	}
	else
		return (EXIT_FAILURE);
}

int	wait_child(pid_t pid)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
		exit_msg(EXIT_FAILURE, STDERR_FILENO, "fail waitpid\n");
	return (_trans_status(status));
}

pid_t	_get_last_pid(t_command *command)
{
	while (command->next)
		command = command->next;
	return (command->pid);
}

int	wait_childs(t_pipeline *pipeline)
{
	const pid_t	last_pid = _get_last_pid(pipeline->commands);
	pid_t		pid;
	int			status;
	int			last_status;

	last_status = 1;
	// printf("last_pid: %d\n", last_pid);
	while (42)
	{
		pid = wait(&status);
		// printf("🐚 wait_childs: in pid=>%d\n", pid);
		if (pid == -1)
			return (_trans_status(last_status));
		else if (pid == last_pid)
			last_status = status;
	}
}
