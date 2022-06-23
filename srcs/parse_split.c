#include "../include/minishell.h"

bool	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

bool	is_space(char c)
{
	return (c == ' ');
}

char	*ft_trim(char *line, char *s)
{
	return (line);
}

void	stack_push(t_stack *stack, char c)
{
	stack->stack[stack->len] = c;
	(stack->len)++;
}

void	stack_pop(t_stack *stack)
{

}

bool	is_valid(char *line)
{
	t_stack	stack;

	while (*line)
	{
		if (*line == '\"' || *line == '\'')
		{
			if (stack.len == 0 || stack.stack[stack.len] != *line)
				stack_push(&stack, *line);
			else
				stack_pop(&stack);
		}
	}
	if (stack.len == 0)
		return (true);
	else
		return (false);
}

void    f(char *line)
{
	int		flag[2];//0: ', 1: ""
	char	*first_index;

	flag[0] = 0;
	flag[1] = 0;
	first_index = 0;
	while (*line)
	{
		if (*line == '\'' || *line == '\"')
		{
			if (*line == '\'')
			{
				if (flag[0] == 0)
				{
					flag[0]++;
					first_index = line;
				}
				else
				{
					break ;
				}
			}
			// if (flag[0] == 1)
		}
	}
}

void    handle_token(char *start, char *end)
{
	char	*str;
	char	*origin;

	str = malloc(end - start + 1);
	origin = str;
	while (1)
	{
		*str++ = *start;
		if (start == end)
			break ;
		start++;
	}
	printf("token: |%s|\n", origin);
	free(origin);
}

#include <string.h>

void    seperate_by_space(char *line)
{
	t_stack	stack;
	char	*first_index;

	memset(&stack, 0, sizeof(t_stack));
	first_index = line;
	while (*line)
	{
		// 목표: space 기준으로 토큰 분리.
		if (is_quote(*line))
		{
			if (stack.len == 0 || stack.stack[stack.len] != *line)
			{
				// 1. quote 처음 만났을때. && 2. 닫히는 quote가 아닌 quote를 만났을때.
				// if (stack.len == 0)
					// first_index = line;
				stack_push(&stack, *line);
			}
			else
			{
				stack_pop(&stack);
				// if (stack.len == 0)
				// {
				// 	handle_token(first_index, line);
				// 	first_index = line + 1;
				// }
			}
		}
		// if (is_space(*line))
		else if (is_space(*line) && stack.len == 0)
		{
			if (first_index != line)
				handle_token(first_index, line - 1);
			first_index = line + 1;//"cat 123 "=> "123 "
		}
		line++;
	}
	if (first_index != line)
		handle_token(first_index, line - 1);
}

// int	main(void)
// {
// 	seperate_by_space("tr 'a' ' '");
// 	printf("=======================\n");
// 	seperate_by_space("echo 123\' 456 \" 123 \' 234 \" \" \' \" \'");
// 	printf("=======================\n");
// 	seperate_by_space("echo 333\'444\'555");
// 	printf("=======================\n");

	
// }

void    parse_split(char *line)
{
	// 1. ""
	char    *trimed;

	// char    stack[1000];
	// ft_memset(stack, (size_t)1000);
	
	// 1.trim
	trimed = ft_trim(line, "123");
	if (!is_valid(trimed))
		exit(1);
	// 2. space => token 분리
	// 2. '문자열치환'
	seperate_by_space(trimed);
}