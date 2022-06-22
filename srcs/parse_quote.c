#include "../include/minishell.h"

void	test_list(t_str	*head)
{
	t_str	*cur;

	cur = head;
	while (cur)
	{
		printf("%s\n", cur->str);
		cur = cur->next;
	}
	printf("res: |");
	cur = head;
	while (cur)
	{
		printf("%s", cur->str);
		cur = cur->next;
	}
	printf("|\n");
}

char	*make_str(char *front, char *end)
{
	char	*p;
	char	*ret;
	int		i;

	ret = malloc(end - front + 2);
	if (ret == NULL)
		return (NULL);//에러 종료
	p = front;
	i = -1;
	while (p + ++i <= end)
		ret[i] = p[i];
	ret[i] = '\0';
	return (ret);
}

t_str	*new_list(char *s)
{
	t_str	*ret;
	
	ret = malloc(sizeof(t_str));
	memset(ret, 0, sizeof(t_str));
	if (ret == NULL)
		return (NULL);//에러 슈팅
	ret->str = s;
	return (ret);
}

void	addstr_list(t_str **str, char *s)
{
	t_str	*cur;

	printf("added => |%s|\n", s);
	cur = *str;
	if (cur == NULL)
		*str = new_list(s);
	else
	{
		while (cur->next)
			cur = cur->next;
		cur->next = new_list(s);
	}
}

void	parse_quote(char *s)
{
	// s: 12'3a'bc'45'6 => 123abc456
	// s: 123\' 456 \" 123 \' 234 \" \" \' \" \'
	// => 123 456 \" 123 \' 234 \" \" \' \" 

	t_str	*parse_str;
	char	*p;
	
	while (*s)
	{
		p = s;
		while (*s != '\'' && *s != '\"' && *s != '\0')
			s++;
		if (p != s)
		{
			addstr_list(&parse_str, make_str(p, s - 1));
			//1. 쿼츠밖 구간; p ~ s-1
			if (*s == '\0')
				break ;
		}
		p = s;
		if (*s == '\'')
		{
			s++;
			while (*s != '\'')
				s++;
		}
		if (p != s)//2. 싱글쿼츠 안(싱글쿼츠 포함): p ~ s, (불포함): p+1 ~ s-1
		{
			addstr_list(&parse_str, make_str(p + 1, s - 1));
			s++;
		}
		p = s;
		if (*s == '\"')
		{
			s++;
			while (*s != '\"')
				s++;
		}
		if (*s == '\"')//3. 더블쿼츠 안(더블쿼츠 포함): p ~ s, (불포함): p+1 ~ s-1
		{
			addstr_list(&parse_str, make_str(p + 1, s - 1));
			s++;
		}
	}
	test_list(parse_str);
}

int	main(void)
{
	// parse_quote("12'3a'bc'45'6");
	// parse_quote("123\' 456 \" 123 \' 234 \" \" \' \" \'");
	parse_quote("123\'abc 123 \" \' 456 \" \" \' \" \'");
	//123 456 " 123 ' 234 " " ' " 
}