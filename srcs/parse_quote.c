#include "minishell.h"

void	_temp_join(t_list *head, char *res)
{
	t_list	*cur;
	char	*s;

	*res = 0;
	cur = head;
	while (cur)
	{
		s = (char *)cur->content;
		while (*s)
			*res++ = *s++;
		cur = cur->next;
	}
	*res = '\0';
}

void	_temp_size(t_list *head, size_t	*res)
{
	t_list	*cur;

	*res = 0;
	cur = head;
	while (cur)
	{
		*res = *res + ft_strlen((const char *)cur->content);
		cur = cur->next;
	}
}

void	_temp_print(t_list *head)
{
	t_list	*cur;

	cur = head;
	while (cur)
	{
		printf("==%s==\n", (char *)cur->content);
		cur = cur->next;
	}
	printf("\n");
}

void	_parse_out_quote(char **p, t_list **head)
{
	char	*s;
	char	*front;
	char	*ret;
	t_list	*new_node;

	s = *p;
	front = *p;
	while (*s != S_QUOTE && *s != D_QUOTE && *s != '\0')
		s++;
	if (front != s)
	{
		ret = ft_substr(front, 0, (size_t)(s - front));
		new_node = ft_lstnew((void *)ret);
		if (ret == NULL || new_node == NULL)
		{
			ft_safe_free((void **)&ret);
			exit(EXIT_FAILURE);
		}
		ft_lstadd_back(head, new_node);
		*p = s;
	}
}

void	_parse_single_quote(char **p, t_list **head)
{
	char	*s;
	char	*front;
	char	*ret;
	t_list	*new_node;

	s = *p;
	front = *p;
	if (*front == S_QUOTE)
	{
		s++;
		while (*s != S_QUOTE)
			s++;
		ret = ft_substr(front, 1, (size_t)(s - front - 1));
		new_node = ft_lstnew((void *)ret);
		if (ret == NULL || new_node == NULL)
		{
			ft_safe_free((void **)&ret);
			exit(EXIT_FAILURE);
		}
		ft_lstadd_back(head, new_node);
		*p = s + 1;
	}
}

void	_parse_double_quote(char **p, t_list **head)
{
	char	*s;
	char	*front;
	char	*ret;
	t_list	*new_node;

	s = *p;
	front = *p;
	if (*front == D_QUOTE)
	{
		s++;
		while (*s != D_QUOTE)
			s++;
		ret = ft_substr(front, 1, (size_t)(s - front - 1));
		new_node = ft_lstnew((void *)ret);
		if (ret == NULL || new_node == NULL)
		{
			ft_safe_free((void **)&ret);
			exit(EXIT_FAILURE);
		}
		ft_lstadd_back(head, new_node);
		*p = s + 1;
	}
}

void	parse_quote(char *s)
{
	t_list	*lst;
	size_t	total_size;
	char	*p;

	lst = NULL;
	while (*s)
	{
		_parse_out_quote(&s, &lst);
		_parse_single_quote(&s, &lst);
		_parse_double_quote(&s, &lst);
	}
	// 링크드 리스트완성

	// 링크드리스트 => join까지 대충 시행.
	_temp_print(lst);
	_temp_size(lst, &total_size);
	printf("size => %zu\n", total_size);
	char	*temp = malloc(total_size + 1);
	if (temp)
	{
		_temp_join(lst, temp);
		printf("joined => %s\n", temp);
	}
}

// int	main(void)
// {
// 	// parse_quote("12'3a'bc'45'6");
// 	parse_quote("123\' 456 \" 123 \' 234 \" \" \' \" \'");
// 	// parse_quote("123\'abc 123 \" \' 456 \" \" \' \" \'");
// 	//123 456 " 123 ' 234 " " ' " 
// }