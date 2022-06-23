/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonjan <hyeonjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 17:29:18 by hyeonjan          #+#    #+#             */
/*   Updated: 2022/06/23 18:00:17 by hyeonjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	size;
	size_t	i;
	size_t	size_t_start;
	char	*ret;

	size_t_start = (size_t) start;
	size = ft_strlen(s);
	if (size <= size_t_start)
		len = 0;
	else if (size <= len)
		len = size;
	ret = malloc(sizeof(char) * (len + 1));
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ret[i] = s[size_t_start + i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}