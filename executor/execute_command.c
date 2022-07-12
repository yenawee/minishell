/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenawee <yenawee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 21:54:54 by hyeonjan          #+#    #+#             */
/*   Updated: 2022/07/12 13:38:01 by yenawee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_alert_join_path(char *path, char *cmd)
{
	char	*ret;
	size_t	size;

	if (ft_strchr(path, ':'))
	{
		size = ft_strchr(path, ':') - path + ft_strlen(cmd) + 2;
		ret = ft_alert_calloc(size, 1);
		ft_strlcat(ret, path, ft_strchr(path, ':') - path + 1);
	}
	else
	{
		size = ft_strlen(path) + ft_strlen(cmd) + 2;
		ret = ft_alert_calloc(size, 1);
		ft_strlcat(ret, path, size);
	}
	ft_strlcat(ret, "/", size);
	ft_strlcat(ret, cmd, size);
	return (ret);
}

int	search_execve(t_sh *sh, t_command *command, char **envp)
{
	const char	*path = find_value_in_env("PATH", sh->env_list);
	char *const	cmd = command->argv[0];
	char		*path_cmd;
	int			file_type;

	if (*cmd == '\0' || *path == '\0')
		return (1);
	while (42)
	{
		if (*path == '/')
		{
			path_cmd = ft_alert_join_path((char *)path, command->argv[0]);
			file_type = check_ftype(path_cmd);
			if (file_type == FT_DIR)
				exit_command_perror_msg(126, cmd, "is a directory");
			else if (file_type == FT_FILE && \
					execve(path_cmd, command->argv, envp))
				exit_command_perror_msg(126, cmd, strerror(errno));
			free(path_cmd);
		}
		path = ft_strchr(path, ':');
		if (path == NULL)
			return (1);
		path++;
	}
}

/**
 * @brief simple의 기준이 무엇인지 아직 모르겠음
 *
 * @param sh
 * @param command
 * @param tokens
 * @param token_size
 */
void	execute_simple_cmd(t_sh *sh, t_command *command, char **envp)
{
	char		**argv;
	int			ftype;
	char *const	cmd = command->argv[0];

	if (ft_strchr(cmd, '/'))
	{
		ftype = check_ftype(cmd);
		if (ftype == FT_NOTFOUND)
			exit_command_perror_msg(127, cmd, strerror(errno));
		else if (ftype == FT_DIR)
			exit_command_perror_msg(126, cmd, "is a directory");
		else if (execve(cmd, argv, envp))
			exit_command_perror_msg(127, cmd, strerror(errno));
	}
	search_execve(sh, command, envp);
	exit_command_perror_msg(127, cmd, "command not found");
}
