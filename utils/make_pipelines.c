/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_pipelines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonjan <hyeonjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 22:07:35 by hyeonjan          #+#    #+#             */
/*   Updated: 2022/07/04 22:21:15 by hyeonjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	set_command(t_command *command, t_token *tokens)
{
	command->tokens = tokens;
	if (command->token_size == 0)
		return (FAIL);
	return (SUCCESS);
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
		return (FAIL);
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