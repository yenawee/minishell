/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonjan <hyeonjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 15:38:07 by hyeonjan          #+#    #+#             */
/*   Updated: 2022/07/08 20:17:52 by hyeonjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	_swap(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

static void	_swap_pipe(t_pipes *p)
{
	_swap(&(p->prev_pipe[READ]), &(p->next_pipe[READ]));
	_swap(&(p->prev_pipe[WRITE]), &(p->next_pipe[WRITE]));
}

static void	_pipe_init(t_pipes *p)
{
	p->prev_pipe[READ] = -1;
	p->prev_pipe[WRITE] = -1;
	p->next_pipe[READ] = -1;
	p->next_pipe[WRITE] = -1;
}

int	execute_pipeline(t_sh *sh, t_pipeline *pipeline, char **envp)
{
	t_pipes		p;
	t_command	*command;

	_pipe_init(&p);
	command = pipeline->commands;
	while (command)
	{
		_swap_pipe(&p);
		if (command->next && pipe(p.next_pipe) == -1)
			exit_msg(EXIT_FAILURE, sh->fd_stderr, "fail pipe()\n");
		command->pid = fork();
		if (command->pid == -1)
			exit_msg(EXIT_FAILURE, sh->fd_stderr, "fail fork()\n");
		else if (command->pid == 0)
			fork_execute_command(sh, &p, command, envp);
		else
		{
			ft_alert_safe_close(&p.prev_pipe[READ]);
			ft_alert_safe_close(&p.next_pipe[WRITE]);
		}
		command = command->next;
	}
	return (wait_childs(pipeline));
}
