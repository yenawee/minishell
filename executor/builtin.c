/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonjan <hyeonjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 21:59:32 by hyeonjan          #+#    #+#             */
/*   Updated: 2022/07/07 22:00:49 by hyeonjan         ###   ########.fr       */
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

	return (1);
	// cmd = command->argv[0];
	// if (ft_strcmp(cmd, "echo") == 0)
	// 	return (ft_echo(command));
	// else if (ft_strcmp(cmd, "cd") == 0)
	// 	return (ft_cd(command));
	// else if (ft_strcmp(cmd, "pwd") == 0)
	// 	return (ft_pwd(command));
	// else if (ft_strcmp(cmd, "export") == 0)
	// 	return (ft_export(command));
	// else if (ft_strcmp(cmd, "unset") == 0)
	// 	return (ft_unset(command));
	// else if (ft_strcmp(cmd, "env") == 0)
	// 	return (ft_env(command));
	// else if (ft_strcmp(cmd, "exit") == 0)
	// 	return (ft_exit(command));
	// else
	// 	return (1);
}
