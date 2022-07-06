#include "../include/minishell.h"

t_token	*define_type(t_token *list)
{
	t_token	*curr;

	curr = list;
	while (curr)
	{
		if (!ft_strcmp(curr->str, "|"))
			curr->type = T_PIPE;
		else if (!ft_strcmp(curr->str, ">") || !ft_strcmp(curr->str, "<"))
			curr->type = T_REDIRECT;
		else if (!ft_strcmp(curr->str, "<<"))
			curr->type = T_HEREDOC;
		else if (!ft_strcmp(curr->str, ">>"))
			curr->type = T_APPEND;
		else if (!ft_strcmp(curr->str, "||"))
			curr->type = T_OR;
		else if (!ft_strcmp(curr->str, "&&"))
			curr->type = T_AND;
		else if (curr->prev && (curr->prev->type == T_REDIRECT \
		|| curr->prev->type == T_APPEND))
			curr->type = T_FILE;
		else
			curr->type = T_WORD;
		curr = curr->next;
	}
	return (list);
}
