#include "../include/minishell.h"

t_token	*define_type(t_token *list)
{
	t_token	*curr;

	curr = list;
	while (curr)
	{
		if (!ft_strcmp(curr->str, "|"))
			curr->type = T_PIPE;
		else if (!ft_strcmp(curr->str, ">"))
			curr->type = T_RRDIR;
		else if (!ft_strcmp(curr->str, "<"))
			curr->type = T_LRDIR;
		else if (!ft_strcmp(curr->str, "<<"))
			curr->type = T_HEREDOC;
		else if (!ft_strcmp(curr->str, ">>"))
			curr->type = T_APPEND;
		else if (!ft_strcmp(curr->str, "||"))
			curr->type = T_OR;
		else if (!ft_strcmp(curr->str, "&&"))
			curr->type = T_AND;
		else if (curr->prev && (curr->prev->type == T_RRDIR \
		|| curr->prev->type == T_LRDIR || curr->prev->type == T_APPEND))
			curr->type = T_FILE;
		else if (curr->prev && curr->prev->type == T_HEREDOC)
			curr->type = T_LIMITER;
		else
			curr->type = T_WORD;
		curr = curr->next;
	}
	return (list);
}
