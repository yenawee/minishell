/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_no_arg_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenawee <yenawee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 18:41:31 by yenawee           #+#    #+#             */
/*   Updated: 2022/07/10 18:44:26 by yenawee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	_export_print(t_env *ret)
{
	if (ret->value)
	{
		ft_putstr_fd(STDOUT_FILENO, "declare -x ");
		ft_putstr_fd(STDOUT_FILENO, ret->key);
		ft_putstr_fd(STDOUT_FILENO, "=\"");
		ft_putstr_fd(STDOUT_FILENO, ret->value);
		ft_putstr_fd(STDOUT_FILENO, "\"\n");
	}
	else
	{
		ft_putstr_fd(STDOUT_FILENO, "declare -x ");
		ft_putstr_fd(STDOUT_FILENO, ret->key);
		ft_putstr_fd(STDOUT_FILENO, "\n");
	}
}
