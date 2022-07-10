/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenawee <yenawee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 18:31:34 by yenawee           #+#    #+#             */
/*   Updated: 2022/07/10 20:07:40 by yenawee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_isalpha(int c)
{
	if (c >= 'a' && c <= 'z')
		return (2);
	else if (c >= 'A' && c <= 'Z')
		return (1);
	else
		return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	else
		return (0);
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	ft_isoperator(char c)
{
	return (c == '|' || c == '>' || c == '<');
}
