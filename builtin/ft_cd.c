/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonjan <hyeonjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 18:26:57 by yenawee           #+#    #+#             */
/*   Updated: 2022/07/14 10:56:01 by hyeonjan         ###   ########.fr       */
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

static void	_alert_getcwd(char **pwd)
{
	*pwd = getcwd(NULL, 0);
	if (*pwd == NULL)
		exit_msg(EXIT_FAILURE, STDERR_FILENO, "fail getcwd()\n");
}

static int	_handle_prev_path(char *str, char **target, t_list *env_list, int *print_pwd)
{
	*target = NULL;
	*print_pwd = 0;
	if (str == NULL || ft_strcmp(str, "-") != 0)
		return (SUCCESS);
	*target = get_env_value(env_list, "OLDPWD");
	*print_pwd = 1;
	if (*target == NULL)
	{
		ft_putstr_fd(STDERR_FILENO, "minishell: cd: OLDPWD not set\n");
		return (FAIL);
	}
	return (SUCCESS);
}

static int	_handle_home(char *str, char **target, t_list *env_list)
{
	if (!str || ft_strcmp(str, "~") == 0 || (str[0] == '~' && str[1] == '/'))
	{
		*target = get_env_value(env_list, "HOME");
		if (*target == NULL)
		{
			ft_putstr_fd(STDERR_FILENO, "🐚: cd: HOME not set\n");
			return (FAIL);
		}
		ft_alert_str_append(target, str + 1 + (str[1] == '/'));
	}
	else if (*target == NULL)
		*target = ft_alert_strdup(str);
	return (SUCCESS);
}

int	ft_cd(t_list *env_list, char **argv)
{
	char	*oldpwd;
	char	*target;
	char	*cwd;
	int		print_pwd;

	if (!_handle_prev_path(argv[1], &target, env_list, &print_pwd) || \
		!_handle_home(argv[1], &target, env_list))
		return (EXIT_FAILURE);
	_alert_getcwd(&oldpwd);
	if (chdir(target) == -1)
	{
		ft_putstr_fd(STDERR_FILENO, "minishell: cd: ");
		ft_putstr_fd(STDERR_FILENO, strerror(errno));
		ft_putstr_fd(STDERR_FILENO, "\n");
		return (_return(EXIT_FAILURE, target, oldpwd, NULL));
	}
	_alert_getcwd(&cwd);
	if (print_pwd)
		printf("%s\n", cwd);
	ft_export_one(&env_list, "PWD", cwd, 0);
	ft_export_one(&env_list, "OLDPWD", oldpwd, 0);
	return (_return(EXIT_SUCCESS, target, oldpwd, cwd));
}
