#include "../include/minishell.h"

void	test_command(t_command *command, int i)
{
	t_token	*cur_token;
	int		j;

	printf("=== test_command[%d] ===\n", i);
	printf("=== size: %d ===\n", command->token_size);
	j = 0;
	cur_token = command->tokens;
	while (j < command->token_size)
	{
		printf("token[%d] => |%s|, %d\n", ++j, cur_token->str, cur_token->type);
		cur_token = cur_token->next;
	}
}

void	test_pipeline(t_pipeline *pipeline, int i)
{
	int	j;
	t_command	*cur_command;

	printf("=== test_pipeline[%d] ===\n", i);
	j = 0;
	cur_command = pipeline->commands;
	while (cur_command)
	{
		test_command(cur_command, ++j);
		cur_command = cur_command->next;
	}
}

void	test_list(t_pipeline *list)
{
	t_pipeline	*cur_pipeline;
	int	i;

	printf("=== test_list ===\n");
	i = 0;
	cur_pipeline = list;
	while (cur_pipeline)
	{
		test_pipeline(cur_pipeline, ++i);
		cur_pipeline = cur_pipeline->next;
	}
}