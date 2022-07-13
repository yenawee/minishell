/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_out_of_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonjan <hyeonjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 20:25:19 by hyeonjan          #+#    #+#             */
/*   Updated: 2022/07/13 21:31:16 by hyeonjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*_attach_double_quote(char *str, int need_blank)
{
	char	*ret;
	size_t	size;

	if (str == NULL || *str == '\0')
		return (str);
	size = ft_strlen(str) + need_blank;
	ret = ft_alert_calloc(size + 3, sizeof(char));
	ret[0] = '\"';
	if (need_blank)
	{
		ret[0] = ' ';
		ret[1] = '\"';
	}
	ft_strlcat(ret, str, size + 3);
	ret[size + 1] = '\"';
	return (ret);
}

static char	*_add_dqoute_blank(char *str, char *p, char *front, char *ret)
{
	if (str == NULL)
		return (NULL);
	while (*p && ft_strchr(" \t", *p))
		p++;
	while (*p)
	{
		front = p;
		while (*p && !ft_strchr(" \t", *p))
		{
			if (ft_strchr("\'\"", *p))
				p = ft_strchr(p + 1, *p);
			p++;
		}
		if (*p)
			*p++ = '\0';
		ft_alert_added(&ret, _attach_double_quote(front, ret != NULL));
		while (*p && ft_strchr(" \t", *p))
			p++;
	}
	free(str);
	return (ret);
}

static void	*_expand_variable(t_sh *sh, char **ret, char *var)
{
	char	*key;
	char	*malloced_val;
	size_t	i;

	if (*var == '?')
	{
		*ret = var + 1;
		return (ft_alert_itoa(sh->exit_status));
	}
	i = 1;
	while (var[i] == '_' || ft_isalnum(var[i]))
		i++;
	*ret = &var[i];
	key = ft_alert_substr(var, 0, i);
	malloced_val = get_env_value(sh->env_list, key);
	safe_free((void **)&key);
	return (_add_dqoute_blank(malloced_val, malloced_val, malloced_val, NULL));
}

char	*expand_out_of_quote(t_sh *sh, char *str, char *p, char *ret)
{
	while (42)
	{
		while (*p && !ft_strchr("\'\"$", *p))
			p++;
		if (*p == '\0')
		{
			ft_alert_str_append(&ret, str);
			break ;
		}
		else if (ft_strchr("\'\"", *p))
			p = ft_strchr(p + 1, *p) + 1;
		else if (*p == '$' && !ft_strchr("_?", p[1]) && !ft_isalpha(p[1]))
			p++;
		else if (*p == '$')
		{
			ft_alert_added(&ret, ft_alert_substr(str, 0, p - str));
			ft_alert_added(&ret, _expand_variable(sh, &str, &p[1]));
			p = str;
		}
	}
	return (ret);
}
