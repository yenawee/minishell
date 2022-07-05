#include "../include/minishell.h"

// int	g_status;

// int	ft_exit(t_list *args)
// {
// 	const	ac = ft_lstsize(args);
// 	int	status;

// 	if (isatty(STDIN_FILENO))
// 		printf("exit\n");
// 	if (ac > 2)
// 	{
// 		printf("exit: too many arguments\n");
// 		return (EXIT_FAILURE);
// 	}
// 	if (ac == 0)
// 		status = g_status;
// 	else if (!ft_atoi(((t_token *)args->content)->str, &status))
// 	{
// 		status = 255;
// 		printf("exit: numeric argument required\n");
// 	}
// 	exit(status);
// }

// int main(void)
// {
// 	pid_t	pid;
// 	int		status;

// 	status = -1;
// 	pid = fork();
// 	if (pid == 0)
// 		exit(2 & 0xff);
// 	else
// 		waitpid(pid, &status, WUNTRACED);
// 	printf("exit_status: %d\n", status);
// 	if (WIFEXITED(status))
// 		printf("exit_status2: %d\n", WEXITSTATUS(status));
// }
