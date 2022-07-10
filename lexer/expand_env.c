/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenawee <yenawee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 19:40:49 by yenawee           #+#    #+#             */
/*   Updated: 2022/07/10 19:40:50 by yenawee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*expand_env_if(char **str, t_sh *sh, char *dlr_pos)
{
	char	*env_value;
	char	*key;

	if (**str == '?')
	{
		env_value = ft_strdup(ft_itoa(sh->exit_status));
		(*str)++;
	}
	else if (is_valid_key_first(**str))
	{
		while (is_valid_key_last(**str))
			(*str)++;
		key = ft_substr(dlr_pos + 1, 0, *str - dlr_pos - 1);
		env_value = ft_strdup(find_value_in_env(key, sh->env_list));
		safe_free(&key);
	}
	else
		env_value = ft_strdup("$");
	return (env_value);
}

char	*expand_env(char *str, t_sh *sh)
{
	char	*ret;
	char	*str_slice;
	char	*env_value;
	char	*dlr_pos;

	ret = NULL;
	while (*str)
	{
		dlr_pos = ft_strchr(str, '$');
		if (!dlr_pos)
		{
			ft_safe_strjoin(&ret, str);
			break ;
		}
		str_slice = ft_substr(str, 0, dlr_pos - str);
		ft_safe_strjoin(&ret, str_slice);
		str = dlr_pos + 1;
		env_value = expand_env_if(&str, sh, dlr_pos);
		ft_safe_strjoin(&ret, env_value);
	}
	return (ret);
}
