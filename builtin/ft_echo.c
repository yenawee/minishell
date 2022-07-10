/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenawee <yenawee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 18:28:35 by yenawee           #+#    #+#             */
/*   Updated: 2022/07/10 18:28:52 by yenawee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static int	check_echo_index(char **s)
{
	int	ret_idx;
	int	j;

	ret_idx = 2;
	while (s[ret_idx])
	{
		j = 1;
		if (s[ret_idx][0] != '-')
			return (ret_idx);
		else
		{
			while (s[ret_idx][j] == 'n')
				j++;
			if (s[ret_idx][j] != '\0')
				return (ret_idx);
		}
		ret_idx++;
	}
	return (ret_idx);
}

int	ft_echo(char **argv)
{
	int	new_line_opt_flag;
	int	i;

	new_line_opt_flag = check_echo_opt(argv[1]);
	if (new_line_opt_flag)
		i = check_echo_index(argv);
	else
		i = 1;
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
