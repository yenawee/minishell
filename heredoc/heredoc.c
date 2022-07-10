/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonjan <hyeonjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 16:37:12 by hyeonjan          #+#    #+#             */
/*   Updated: 2022/07/10 16:39:18 by hyeonjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	_set_heredoc(char **file_name, int *fd, int i)
{
	char				buf[11];
	const char			*alnum = "0123456789abcdef";

	ft_strlcpy(buf, "./heredoc", 11);
	buf[9] = alnum[i];
	buf[10] = '\0';
	*file_name = ft_alert_strdup(buf);
	*fd = open(*file_name, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (*fd < 0)
		exit_msg(EXIT_FAILURE, STDERR_FILENO, "fail open()\n");
}

int	_read_from_heredoc(char **eof, t_list *env_list, int i)
{
	char	*file_name;
	int		fd;
	char	*input;

	input = NULL;
	_set_heredoc(&file_name, &fd, i);
	while (42)
	{
		safe_free((void **)&input);
		input = readline("heredoc 🐚 > ");
		if (input == NULL || ft_strcmp(input, *eof) == 0)//어느때 NULL이 생기는지 확인해야함! => 시그널로 추측
		{
			break ;
		}
		expand_in_heredoc(input, fd, env_list);
	}
	close(fd);
	safe_free(eof);
	*eof = file_name;
	if (input == NULL)//어느때 NULL이 생기는지 확인해야함! => 시그널로 추측
		return (FAIL);
	safe_free((void **)&input);
	return (SUCCESS);
}

int	_is_over_max_heredoc(t_token *tokens)
{
	t_token	*cur;
	int		cnt;

	cnt = 0;
	cur = tokens;
	while (cur)
	{
		if (cur->type == T_HEREDOC && ++cnt > MAX_HEREDOC)
			return (FAIL);
		cur = cur->next;
	}
	return (SUCCESS);
}

//cat << eof && cat << eof && cat << eof && cat << eof && cat << eof && cat << eof && cat << eof && cat << eof && cat << eof && cat << eof && cat << eof && cat << eof && cat << eof && cat << eof && cat << eof && cat << eof && cat << eof
int	handle_heredoc(t_token *tokens, t_list *env_list)
{
	t_token	*cur;
	int		i;

	if (!_is_over_max_heredoc(tokens))
	{
		ft_putstr_fd(STDERR_FILENO, "🐚: maximum here-document count exceeded\n");
		return (FAIL);
	}
	i = 0;
	cur = tokens;
	while (cur)
	{
		if (cur->type == T_HEREDOC && \
			!_read_from_heredoc(&cur->next->str, env_list, i++))
			return (FAIL);
		cur = cur->next;
	}
	return (SUCCESS);
}
