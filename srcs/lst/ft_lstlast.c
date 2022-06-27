/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywee <ywee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 18:05:38 by hyeonjan          #+#    #+#             */
/*   Updated: 2022/06/27 17:16:46 by ywee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*cur;

	if (!lst)
		return (NULL);
	cur = lst;
	while (cur->next)
		cur = cur->next;
	return (cur);
}
