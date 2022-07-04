#include "../include/minishell.h"

static int	check_echo_opt(char *s)
{
	int	i;

	i = 1;
	if (s[0] != '-')
		return (FALSE);
	while (s[i])
	{
		if (s[i] != 'n')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	ft_echo(char **argv)
{
	int	new_line_opt_flag;
	int	i;

	new_line_opt_flag = check_echo_opt(argv[1]);
	i = 1;
	i += new_line_opt_flag;
	// exit_failure 반환할 때 ?? -> 없는거같은디 ??
	while (argv[i])
	{
		ft_putstr_fd(STDOUT_FILENO, argv[i]);
		if (argv[i + 1])
			ft_putstr_fd(STDOUT_FILENO, " ");
		i++;
	}
	if (!new_line_opt_flag)
		ft_putstr_fd(STDOUT_FILENO, "\n");
	return (EXIT_SUCCESS);
}

// int main()
// {
// 	char *argv[] = {"echo", "--n", "hi", "good", NULL};
// 	ft_echo(argv);
// 	return 0;
// }
