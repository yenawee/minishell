/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonjan <hyeonjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 14:17:33 by hyeonjan          #+#    #+#             */
/*   Updated: 2022/07/06 14:30:44 by hyeonjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*ret;

	ret = ft_calloc(1, sizeof(t_list));
	if (ret == NULL)
		return (NULL);
	ret->content = content;
	return (ret);
}

t_list	*ft_alert_lstnew(void *content)
{
	t_list	*ret;

	ret = ft_lstnew(content);
	if (ret == NULL)
		exit_msg(EXIT_FAILURE, STDERR_FILENO, "malloc error\n");
	return (ret);
}
