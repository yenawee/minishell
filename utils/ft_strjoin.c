/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonjan <hyeonjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 20:06:44 by yenawee           #+#    #+#             */
/*   Updated: 2022/07/12 21:18:01 by hyeonjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_safe_strjoin(char **ret, char *str)
{
	char	*tmp;

	tmp = *ret;
	*ret = ft_strjoin(*ret, str);
	safe_free((void **)&tmp);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*rst;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	rst = ft_calloc(sizeof(char), (s1_len + s2_len + 1));
	if (!rst)
		return (NULL);
	ft_strlcpy(rst, s1, s1_len + 1);
	ft_strlcpy(rst + s1_len, s2, s2_len + 1);
	return (rst);
}

char	*ft_alert_strjoin(char const *s1, char const *s2)
{
	char	*rst;

	rst = ft_strjoin(s1, s2);
	if (rst == NULL)
		exit_msg(EXIT_FAILURE, STDERR_FILENO, "malloc error\n");
	return (rst);
}

void	ft_alert_str_append(char **prev, char *added)
{
	char	*ret;

	if (added == NULL || *added == '\0')
		return ;
	if (*prev == NULL && added == NULL)
		ret = ft_alert_strdup("");
	else
		ret = ft_alert_strjoin((char const *)*prev, (char const *)added);
	safe_free((void **)prev);
	*prev = ret;
}

void	ft_alert_added(char **prev, char *added)
{
	char	*ret;

	if (added == NULL)
		return ;
	if (*added == '\0')
	{
		free(added);
		return ;
	}
	ret = ft_alert_strjoin((char const *)*prev, (char const *)added);
	free(added);
	safe_free((void **)prev);
	*prev = ret;
}