/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonjan <hyeonjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 19:40:49 by yenawee           #+#    #+#             */
/*   Updated: 2022/07/14 12:37:22 by hyeonjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*expand_env_if(char **str, t_sh *sh, char *dlr_pos)
{
	char	*env_value;
	char	*key;

	if (**str == '?')
	{
		env_value = ft_itoa(sh->exit_status);
		(*str)++;
	}
	else if (is_valid_key_first(**str))
	{
		while (is_valid_key_last(**str))
			(*str)++;
		key = ft_alert_substr(dlr_pos + 1, 0, *str - dlr_pos - 1);
		env_value = ft_alert_strdup(find_value_in_env(key, sh->env_list));
		safe_free((void **)&key);
	}
	else
		env_value = ft_alert_strdup("$");
	return (env_value);
}

char	*expand_env(char *str, t_sh *sh)
{
	char	*ret;
	char	*str_slice;
	char	*env_value;
	char	*dlr_pos;

	ret = NULL;
	str_slice = NULL;
	env_value = NULL;
	while (*str)
	{
		dlr_pos = ft_strchr(str, '$');
		if (!dlr_pos)
		{
			ft_safe_strjoin(&ret, str);
			break ;
		}
		str_slice = ft_alert_substr(str, 0, dlr_pos - str);
		ft_safe_strjoin(&ret, str_slice);
		safe_free((void **)&str_slice);
		str = dlr_pos + 1;
		env_value = expand_env_if(&str, sh, dlr_pos);
		ft_safe_strjoin(&ret, env_value);
		safe_free((void **)&env_value);
	}
	return (ret);
}
