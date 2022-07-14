/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonjan <hyeonjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 18:26:57 by yenawee           #+#    #+#             */
/*   Updated: 2022/07/13 23:45:42 by hyeonjan         ###   ########.fr       */
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
		target = ft_strdup(str);
	return (target);
}

int	ft_cd(t_list *env_list, char **argv)
{
	char	*oldpwd;
	char	*target;
	char	*cwd;

	cwd = NULL;
	oldpwd = getcwd(NULL, 0);
	target = _get_target(argv[1], env_list);
	if (!target)
		return (_return(EXIT_FAILURE, target, oldpwd, cwd));
	if (chdir(target) == -1)
	{
		ft_putstr_fd(STDERR_FILENO, "minishell: cd: ");
		ft_putstr_fd(STDERR_FILENO, strerror(errno));
		ft_putstr_fd(STDERR_FILENO, "\n");
		return (_return(EXIT_FAILURE, target, oldpwd, cwd));
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (_return(EXIT_FAILURE, target, oldpwd, cwd));
	ft_export_one(&env_list, "PWD", cwd, 0);
	if (oldpwd)
		ft_export_one(&env_list, "OLDPWD", oldpwd, 0);
	return (_return(EXIT_SUCCESS, target, oldpwd, cwd));
}
