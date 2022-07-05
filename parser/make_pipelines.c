/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_pipelines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywee <ywee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 22:07:35 by hyeonjan          #+#    #+#             */
/*   Updated: 2022/07/05 16:09:36 by ywee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	syntax_check_near_arrow(t_token *tokens, int token_size)
{
	t_token	*cur;

	cur = tokens;
	while (token_size)
	{
		--token_size;
		if (((cur->type == T_REDIRECT || cur->type == T_APPEND) && \
			(token_size == 0 || cur->next->type != T_FILE)) || \
			(cur->type == T_HEREDOC && \
			(token_size == 0 || cur->next->type != T_WORD)))
			{
				ft_putstr_fd(STDERR_FILENO, "🐚 > syntax error near unexpected token `");
				if (cur->next)
					ft_putstr_fd(STDERR_FILENO, cur->next->str);
				else
					ft_putstr_fd(STDERR_FILENO, "newline");
				ft_putstr_fd(STDERR_FILENO, "'\n");
				return (FAIL);
			}
		cur = cur->next;
	}
	return (SUCCESS);
}

int	set_command(t_command *command, t_token *tokens)
{
	command->tokens = tokens;
	if (command->token_size == 0)
	{
		ft_putstr_fd(STDERR_FILENO, "🐚 > error111!\n");
		return (FAIL);
	}
	return (syntax_check_near_arrow(tokens, command->token_size));
}

int	make_commands(t_command **commands, t_token *tokens)
{
	t_command	*cur_command;
	t_token		*cur;

	*commands = ft_alert_calloc(1, sizeof(t_command));
	cur_command = *commands;
	cur = tokens;
	while (42)
	{
		if (cur == NULL || cur->type == T_OR || \
			cur->type == T_AND || cur->type == T_PIPE)
		{
			if (set_command(cur_command, tokens) == FAIL)
				return (FAIL);
			if (cur == NULL || cur->type == T_OR || cur->type == T_AND)
				return (SUCCESS);
			cur_command->next = ft_alert_calloc(1, sizeof(t_command));
			cur_command = cur_command->next;
			tokens = cur->next;
			cur = cur->next;
			continue ;
		}
		++(cur_command->token_size);
		cur = cur->next;
	}
}

int	set_pipeline(t_pipeline	*pipeline, t_token *tokens, int seperated_type)
{
	pipeline->seperated_type = seperated_type;
	pipeline->tokens = tokens;
	if (pipeline->token_size == 0)
	{
		ft_putstr_fd(STDERR_FILENO, "🐚 > error222!\n");
		return (FAIL);
	}
	return (make_commands(&pipeline->commands, pipeline->tokens));
}

/**
 * @brief make one list = make pipelines
 *
 * @param pipelines 생성된 파이프라인의 주소를 저장할 주소
 *
 * @param input 파이프라인 생성에 기반 문자열(사용자 입력 전체)
 * @return int 실행결과 (성공 / 실패)
 */
int	make_pipelines(t_pipeline **pipelines, t_token *tokens)
{
	t_pipeline	*cur_pipeline;
	t_token		*cur;

	*pipelines = ft_alert_calloc(1, sizeof(t_pipeline));
	cur_pipeline = *pipelines;
	cur = tokens;
	while (42)
	{
		if (cur == NULL || cur->type == T_OR || cur->type == T_AND)
		{
			if (set_pipeline(cur_pipeline, tokens, cur && cur->type) == FAIL)
				return (FAIL);
			if (cur == NULL)
				return (SUCCESS);
			cur_pipeline->next = ft_alert_calloc(1, sizeof(t_pipeline));
			cur_pipeline = cur_pipeline->next;
			tokens = cur->next;
			cur = cur->next;
			continue ;
		}
		++(cur_pipeline->token_size);
		cur = cur->next;
	}
}

//cat < infile > outfile && export a b=c d=e && export | grep PWD
