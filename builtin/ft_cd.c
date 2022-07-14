/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonjan <hyeonjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 18:26:57 by yenawee           #+#    #+#             */
/*   Updated: 2022/07/14 09:40:09 by hyeonjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	_return(int exit_status, char *p1, char *p2, char *p3)
{
	if (p1)
		free(p1);
	if (p2)
		free(p2);
	if (p3)
		free(p3);
	return (exit_status);
}

static char	*_get_target(char *str, t_list *env_list)
{
	char	*target;

	if (!str || !ft_strcmp(str, "~") || !ft_strcmp(str, "~/"))
		target = get_env_value(env_list, "HOME");
	else if (!ft_strcmp(str, "-"))
		target = get_env_value(env_list, "OLDPWD");
	else
		target = ft_alert_strdup(str);
	return (target);
}

int	ft_cd(t_list *env_list, char **argv)
{
	char	*oldpwd;
	char	*target;
	char	*cwd;

	oldpwd = getcwd(NULL, 0);
	target = _get_target(argv[1], env_list);
	if (!target)
		return (_return(EXIT_FAILURE, target, oldpwd, NULL));
	if (chdir(target) == -1)
	{
		ft_putstr_fd(STDERR_FILENO, "minishell: cd: ");
		ft_putstr_fd(STDERR_FILENO, strerror(errno));
		ft_putstr_fd(STDERR_FILENO, "\n");
		return (_return(EXIT_FAILURE, target, oldpwd, NULL));
	}
	cwd = getcwd(NULL, 0);
	if (!cwd || !oldpwd)
		exit_msg(EXIT_FAILURE, STDERR_FILENO, "fail getcwd()\n");
	ft_export_one(&env_list, "PWD", cwd, 0);
	ft_export_one(&env_list, "OLDPWD", oldpwd, 0);
	return (_return(EXIT_SUCCESS, target, oldpwd, cwd));
}
