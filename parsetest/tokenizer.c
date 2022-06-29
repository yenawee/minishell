#include "test.h"

int check_quote_match(char *str)
{
	int i;

	while (str[i])
		i++;
	i--;
	if (str[0] == '\'' && str[i] != '\'')
		return (FALSE);
	if (str[0] == '\"' && str[i] != '\"')
		return (FALSE);
	if (str[0] != '\'' && str[i] == '\'')
		return (FALSE);
	if (str[0] != '\"' && str[i] == '\"')
		return (FALSE);
	return (TRUE);
}

void	addtoken(t_token **list, char *begin, char *end)
{
	t_token *new_node = malloc(sizeof(t_token));
	t_token *tmp;
	tmp = *list;

	int i = 0;
	char *str = malloc(sizeof(end - begin + 2));
	while (i < end - begin + 1)
	{
		str[i] = begin[i];
		i++;
	}
	str[i] = '\0';
	if (!check_quote_match(str))
	{
		printf("syntax err!");
		exit(EXIT_FAILURE);
	}

	//char *token_str = expand_env(str);
	//free(str);
	// expand variables , quote 떼기
	new_node->str = str;
	new_node->type = 0;
	new_node->next = NULL;
	new_node->prev = NULL;

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

void parse(t_token *list, char *line)
{
	char *begin = ft_strtrim(line, " \n\t");
	char *end;

	while (*begin)
	{
		while (ft_isspace(*begin))
			begin++;
		if (ft_strchr("<>", *begin))
		{
			if (*begin == *(begin + 1))
				end = begin + 1;
			else
				end = begin;
			addtoken(&list, begin, end);
		}
		else if (*begin == '|')
		{
			if (*begin == *(begin + 1))
			{
				printf("syntax err!");
				exit(EXIT_FAILURE);
			}
			end = begin;
			addtoken(&list, begin, end);
		}
		else if (ft_strchr("\"\'", *begin))
		{
			end = ft_strchr(begin + 1, *begin);
			if (!end)
			{
				printf("syntax err!");
				exit(EXIT_FAILURE);
			}
			addtoken(&list, begin, end);
		}
		else if (ft_strchr(";&", *begin))
		{
			printf("syntax err!");
			exit(EXIT_FAILURE);
		}
		else
		{
			end = begin;
			while (*end != '\0' && !ft_isspace(*end) && !ft_isoperator(*end))
				end++;
			end = end - 1;
			addtoken(&list, begin, end);
		}
		begin = end + 1;
	}

	while (list)
	{
		printf("%s\n", list->str);
		list = list->next;
	}
}

int main()
{
	t_token *list;
	list = NULL;
	parse(list, "<infile cat grep \"$abc\" << hi | echo hello");

	return 0;
}
