/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenawee <yenawee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 19:09:13 by yenawee           #+#    #+#             */
/*   Updated: 2022/07/12 13:28:56 by yenawee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	_export_key_and_value(char *str, char *s, \
t_list *list, int *plus_flag)
{
	char	*p;
	char	*key;
	char	*value;

	p = ft_strchr(str, '+');
	if (p + 1 == s)
	{
		*plus_flag = 1;
		*p = '\0';
	}
	*s = '\0';
	key = str;
	value = s + 1;
	if (check_valid_key(key))
		ft_export_one(&list, key, value, *plus_flag);
	else
		ft_putstr_fd(STDERR_FILENO, "not a valid identifier\n");
}

static void	_export(t_list **list, char *str, int *plus_flag)
{
	char	*s;

	s = ft_strchr(str, '=');
	if (!s)
	{
		if (check_valid_key(str))
			ft_export_one(list, str, NULL, *plus_flag);
		else
			ft_putstr_fd(STDERR_FILENO, "not a valid identifier\n");
	}
	else
		_export_key_and_value(str, s, *list, plus_flag);
}

int	ft_export(t_list **list, char **argv)
{
	char	**str;
	int		plus_flag;

	plus_flag = 0;
	if (argv[1] == NULL)
		return (ft_export_no_arg(*list));
	str = ++argv;
	while (*str)
	{
		_export(list, *str, &plus_flag);
		str++;
	}
	return (EXIT_SUCCESS);
}
