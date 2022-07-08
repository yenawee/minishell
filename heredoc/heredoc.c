/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonjan <hyeonjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 16:37:12 by hyeonjan          #+#    #+#             */
/*   Updated: 2022/07/08 22:29:27 by hyeonjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*_u_to_a(unsigned int n, char *buf)
{
	const char	*nu_alpha = "0123456789";

	while (42)
	{
		*(--buf) = nu_alpha[n % 10];
		n /= 10;
		if (n == 0)
			return (buf);
	}
}

void	_set_heredoc(char **file_name, int *fd)
{
	static unsigned int	i = 0;
	char				buf[42];

	*file_name = NULL;
	buf[41] = '\0';
	while (42)
	{
		safe_free(file_name);
		*file_name = ft_strjoin("./heredoc", _u_to_a(i++, &buf[41]));
		*fd = open(*file_name, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
		if (*fd >= 0)
			return ;
	}
}

int	_read_from_heredoc(char **eof, t_list *env_list)
{
	char	*file_name;
	int		fd;
	char	*input;

	input = NULL;
	_set_heredoc(&file_name, &fd);
	while (42)
	{
		safe_free((void **)&input);
		input = readline("heredoc 🐚 > ");
		if (input == NULL || ft_strcmp(input, *eof) == 0)//어느때 NULL이 생기는지 확인해야함! => 시그널로 추측
			break ;
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

	if (!_is_over_max_heredoc(tokens))
	{
		ft_putstr_fd(STDERR_FILENO, "🐚: maximum here-document count exceeded\n");
		return (FAIL);
	}
	cur = tokens;
	while (cur)
	{
		if (cur->type == T_HEREDOC && \
			!_read_from_heredoc(&cur->next->str, env_list))
			return (FAIL);
		cur = cur->next;
	}
	return (SUCCESS);
}
