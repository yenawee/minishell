/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenawee <yenawee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 18:27:24 by yenawee           #+#    #+#             */
/*   Updated: 2022/07/12 12:58:33 by yenawee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	is_string_digit(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static void	check_first_argv(t_sh *sh, char *av)
{
	if (!av)
		return ;
	sh->exit_status = ft_atoi(av);
	if (is_string_digit(av))
		return ;
	ft_putstr_fd(STDOUT_FILENO, "exit\n");
	ft_putstr_fd(STDERR_FILENO, "minishell: exit: ");
	ft_putstr_fd(STDERR_FILENO, av);
	ft_putstr_fd(STDERR_FILENO, ": numeric argument required\n");
	exit(255);
}

int	ft_exit(t_sh *sh, int argc, char **argv)
{
	check_first_argv(sh, *(++argv));
	if (argc > 2)
	{
		ft_putstr_fd(STDOUT_FILENO, "exit\n");
		ft_putstr_fd(STDERR_FILENO, "minishell: exit: too many arguments\n");
		return (EXIT_FAILURE);
	}
	ft_putstr_fd(STDOUT_FILENO, "exit\n");
	exit(sh->exit_status);
}
