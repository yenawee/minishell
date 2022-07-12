/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenawee <yenawee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 19:41:09 by yenawee           #+#    #+#             */
/*   Updated: 2022/07/12 13:34:39 by yenawee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	parse_operator(char **begin, char **end)
{
	while (ft_isspace(**begin))
		(*begin)++;
	*end = *begin;
	if (ft_strchr("<>", **begin))
		*end = *begin + (**begin == *(*begin + 1));
	else if (**begin == '|')
		*end = *begin + (**begin == *(*begin + 1));
	else if (**begin == '&' && *(*begin + 1) == '&')
		*end = *begin + 1;
}

static int	parse_word(char	*begin, char **end)
{
	*end = begin;
	while (**end != '\0' && !ft_isspace(**end) && !ft_isoperator(**end))
	{
		if (ft_strchr("\"\'", **end))
		{
			*end = ft_strchr(*end + 1, **end);
			if (!*end)
				return (FAIL);
		}
		if (**end == '&' && **(end + 1) == '&')
			break ;
		(*end)++;
	}
	*end = *end - 1;
	return (SUCCESS);
}

int	tokenize(t_token **list, char *line)
{
	char	*begin;
	char	*end;

	begin = line;
	while (*begin)
	{
		parse_operator(&begin, &end);
		if (begin == end && !ft_isoperator(*end) && *end != '&')
		{
			if (!parse_word(begin, &end))
			{
				printf("syntax err!\n");
				return (FAIL);
			}
		}
		if (begin <= end)
			addtoken(list, begin, end);
		begin = end + 1;
	}
	*list = define_type(*list);
	return (SUCCESS);
}
