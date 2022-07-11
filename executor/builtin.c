/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonjan <hyeonjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 21:59:32 by hyeonjan          #+#    #+#             */
/*   Updated: 2022/07/11 20:40:18 by hyeonjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_builtin(t_command *command)
{
	char	*cmd;

	cmd = command->argv[0];
	return (ft_strcmp(cmd, "echo") == 0 || \
	ft_strcmp(cmd, "cd") == 0 || \
	ft_strcmp(cmd, "pwd") == 0 || \
	ft_strcmp(cmd, "export") == 0 || \
	ft_strcmp(cmd, "unset") == 0 || \
	ft_strcmp(cmd, "env") == 0 || \
	ft_strcmp(cmd, "exit") == 0);
}

/**
 * @brief 빌트인 함수를 실행 시킨후, 리턴값을 반환하는 함수
 *
 * @param sh
 * @param command
 * @param tokens
 * @param token_size
 * @return int exit_status
 */
int	execute_builtin(t_sh *sh, t_command *command)
{
	char	*cmd;

	cmd = command->argv[0];
	if (ft_strcmp(cmd, "echo") == 0)
		return (ft_echo(command->argv));
	else if (ft_strcmp(cmd, "cd") == 0)
		return (ft_cd(sh->env_list, command->argv));
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(cmd, "export") == 0)
		return (ft_export(&(sh->env_list), command->argv));
	else if (ft_strcmp(cmd, "unset") == 0)
		return (ft_unset(&(sh->env_list), command->argv));
	else if (ft_strcmp(cmd, "env") == 0)
		return (ft_env(sh->env_list));
	else if (ft_strcmp(cmd, "exit") == 0)
		return (ft_exit(sh, command->argc, command->argv));
}
