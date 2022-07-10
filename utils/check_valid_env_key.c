/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_env_key.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenawee <yenawee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 18:31:27 by yenawee           #+#    #+#             */
/*   Updated: 2022/07/10 18:31:58 by yenawee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_valid_key(char *key)
{
	int	len;

	len = ft_strlen(key);
	if (is_valid_key_first(key[0]) && is_valid_key_last(key[len - 1]))
		return (TRUE);
	return (FALSE);
}

int	is_valid_key_first(char c)
{
	return (ft_isalpha(c) || c == '_');
}

int	is_valid_key_last(char c)
{
	return (ft_isalnum(c) || c == '_');
}
