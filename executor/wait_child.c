/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonjan <hyeonjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 21:54:59 by hyeonjan          #+#    #+#             */
/*   Updated: 2022/07/12 16:16:02 by hyeonjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	_trans_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status));
	else
		return (EXIT_FAILURE);
}

int	_signal_print(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			ft_putstr_fd(STDERR_FILENO, "\n");
		else if (WTERMSIG(status) == SIGQUIT)
			ft_putstr_fd(STDERR_FILENO, "Quit: 3\n");
		else
			return (0);
		return (1);
	}
	return (0);
}

int	wait_child(pid_t pid)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
		exit_msg(EXIT_FAILURE, STDERR_FILENO, "fail waitpid\n");
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			ft_putstr_fd(STDERR_FILENO, "\n");
		else if (WTERMSIG(status) == SIGQUIT)
			ft_putstr_fd(STDERR_FILENO, "Quit: 3\n");
	}
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
	int			printed;

	printed = 0;
	last_status = 1;
	while (42)
	{
		pid = wait(&status);
		if (pid == -1)
			return (_trans_status(last_status));
		if (printed == 0)
			printed = _signal_print(status);
		if (pid == last_pid)
			last_status = status;
	}
}
