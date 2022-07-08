#include "../include/minishell.h"

void	_alert_close_pipes(t_pipes *p)
{
	ft_alert_safe_close(&(p->prev_pipe[READ]));
	ft_alert_safe_close(&(p->prev_pipe[WRITE]));
	ft_alert_safe_close(&(p->next_pipe[READ]));
	ft_alert_safe_close(&(p->next_pipe[WRITE]));
}

void	fork_execute_command(t_sh *sh, t_pipes *p, t_command *command, char **envp)
{
	ft_alert_safe_dup2(sh, p->prev_pipe[READ], STDIN_FILENO);
	ft_alert_safe_dup2(sh, p->next_pipe[WRITE], STDOUT_FILENO);
	_alert_close_pipes(p);
	make_cmd_argv(command, sh);
	if (!handle_redirect(sh, command))
		exit(1);
	if (command->argv[0] == NULL)
		exit(0);
	if (is_builtin(command))
		exit(execute_builtin(sh, command));
	else
		execute_simple_cmd(sh, command, envp);
	exit(1);
}