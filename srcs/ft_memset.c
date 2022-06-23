/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonjan <hyeonjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 17:55:11 by hyeonjan          #+#    #+#             */
/*   Updated: 2022/06/23 17:56:45 by hyeonjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;
	unsigned char	uc;
	size_t			i;

	ptr = (unsigned char *)b;
	uc = (unsigned char)c;
	i = 0;
	while (i++ < len)
		*ptr++ = uc;
	return (b);
}