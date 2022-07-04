#include "../include/minishell.h"

int	is_valid_key_first(char c)
{
	return (ft_isalpha(c) || c == '_');
}

int	is_valid_key_last(char c)
{
	return (ft_isalnum(c) || c == '_');
}

int	ft_isalpha(int c)
{
	if (c >= 'a' && c <= 'z')
		return (2);
	else if (c >= 'A' && c <= 'Z')
		return (1);
	else
		return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	else
		return (0);
}

int ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}


int ft_isoperator(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

