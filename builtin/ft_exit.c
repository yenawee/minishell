/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonjan <hyeonjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 18:27:24 by yenawee           #+#    #+#             */
/*   Updated: 2022/07/14 11:13:59 by hyeonjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	_is_string_digit(char *s)
{
	if (*s == '-')
		s++;
	if (*s == '\0')
		return (FALSE);
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (FALSE);
		s++;
	}
	return (TRUE);
}

static void	_check_first_argv(t_sh *sh, char *av)
{
	if (!_is_string_digit(av))
	{
		ft_putstr_fd(STDOUT_FILENO, "exit\n");
		ft_putstr_fd(STDERR_FILENO, "minishell: exit: ");
		ft_putstr_fd(STDERR_FILENO, av);
		ft_putstr_fd(STDERR_FILENO, ": numeric argument required\n");
		exit(255);
	}
	sh->exit_status = ft_atoi(av);
}

int	ft_exit(t_sh *sh, int argc, char **argv)
{
	if (argc == 1 || (argc >= 2 && *(argv[1]) == '\0'))
		_check_first_argv(sh, argv[1]);
	else if (argc > 2)
	{
		ft_putstr_fd(STDOUT_FILENO, "exit\n");
		ft_putstr_fd(STDERR_FILENO, "minishell: exit: too many arguments\n");
		return (EXIT_FAILURE);
	}
	ft_putstr_fd(STDOUT_FILENO, "exit\n");
	exit(sh->exit_status);
}
