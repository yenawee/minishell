/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_wildcard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonjan <hyeonjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 22:21:25 by hyeonjan          #+#    #+#             */
/*   Updated: 2022/07/06 14:37:41 by hyeonjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	match_wildcard(char **file_names, int file_count, \
						t_wildcard **wildcards, int wildcard_count)
{
	int	*arr;
	int	i;
	int	j;
	int	size;

	arr = ft_alert_calloc(file_count, sizeof(int));
	i = -1;
	while (++i < file_count)
	{
		j = -1;
		while (++j < wildcard_count)
		{
			if (is_matched(file_names[i], wildcards[j]))
			{
				arr[i] = 1;
				size++;
				break ;
			}
		}
	}
}
