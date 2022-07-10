#include "../include/minishell.h"

int	get_argc(t_command *cmd)
{
	int			cnt;
	t_token		*cur;
	int			token_size;
	int			i;

	i = 0;
	cnt = 0;
	cur = cmd->tokens;
	while (i < cmd->token_size)
	{
		if (cur->type == T_WORD)
			cnt++;
		i++;
		cur = cur->next;
	}
	return (cnt);
}

void	make_cmd_argv(t_command *cmd, t_sh *sh)
{
	t_token		*cur_token;
	int			i;

	cmd->argc = get_argc(cmd);
	cmd->argv = ft_alert_calloc(cmd->argc + 1, sizeof(char *));
	cur_token = cmd->tokens;
	i = 0;
	while (i < cmd->argc)
	{
		if (cur_token->type == T_WORD)
			cmd->argv[i++] = expand_str(cur_token->str, sh);
		cur_token = cur_token->next;
	}
	cmd->argv[i] = NULL;
}
