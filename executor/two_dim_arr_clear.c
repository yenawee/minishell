/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   two_dim_arr_clear.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonjan <hyeonjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 23:29:29 by hyeonjan          #+#    #+#             */
/*   Updated: 2022/07/07 23:29:29 by hyeonjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	two_dim_arr_clear(char **two_dim_arr)
{
	char	**origin;

	origin = two_dim_arr;
	if (two_dim_arr)
	{
		while (*two_dim_arr)
			free(*two_dim_arr++);
		free(origin);
	}
}
