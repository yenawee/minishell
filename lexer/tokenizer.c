#include "../include/minishell.h"

static void	addtoken(t_token **list, char *begin, char *end, t_list *env_list)
{
	t_token *new_node = ft_calloc(1, sizeof(t_token));
	t_token *tmp;
	tmp = *list;

	int i = 0;
	char *str = malloc(end - begin + 2);
	while (i < end - begin + 1)
	{
		str[i] = begin[i];
		i++;
	}
	str[i] = '\0';
	char *token_str = expand_str(str, env_list);
	new_node->str = token_str;
	if (*list == NULL)
	{
		*list = new_node;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
	new_node->prev = tmp;
}

int	parse(t_token **list, char *line, t_list *env_list)
{
	char	*begin;
	char	*end;

	begin = line;
	while (*begin)
	{
		while (ft_isspace(*begin))
			begin++;
		if (ft_strchr("<>", *begin)) /*	1. 리다이렉션 < && > && << && >>	*/
			end = begin + (*begin == *(begin + 1));
		else if (*begin == '|') /*	2. 파이프	*/
			end = begin + (*begin == *(begin + 1));
		else if (*begin == '&' && *(begin + 1) == '&') /* 3. && */
			end = begin + 1;
		else
		{
			end = begin;
			while (*end != '\0' && !ft_isspace(*end) && !ft_isoperator(*end))
			{
				if (ft_strchr("\"\'", *end))
				{
					end = ft_strchr(end + 1, *end);
					if (!end)
					{
						printf("syntax err!\n");
						return (FAIL);
					}
				}
				if (*end == '&' && *(end + 1) == '&')
					break ;
				end++;
			}
			end = end - 1;
		}
		if (begin <= end)
			addtoken(list, begin, end, env_list);
		begin = end + 1;
	}
	*list = define_type(*list);
	return (SUCCESS);
}
