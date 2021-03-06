/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenawee <yenawee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 18:29:07 by yenawee           #+#    #+#             */
/*   Updated: 2022/07/10 18:29:08 by yenawee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_env(t_list *list)
{
	t_list	*curr;
	t_env	*temp;

	curr = list;
	while (curr)
	{
		temp = (t_env *)curr->content;
		if (temp->value)
		{
			ft_putstr_fd(STDOUT_FILENO, temp->key);
			ft_putstr_fd(STDOUT_FILENO, "=");
			ft_putstr_fd(STDOUT_FILENO, temp->value);
			ft_putstr_fd(STDOUT_FILENO, "\n");
		}
		curr = curr->next;
	}
	return (EXIT_SUCCESS);
}
