/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_no_arg_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonjan <hyeonjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 18:41:31 by yenawee           #+#    #+#             */
/*   Updated: 2022/07/10 20:31:38 by hyeonjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	export_print(t_env *ret)
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
