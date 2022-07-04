#include "../include/minishell.h"

int ft_isoperator(char c)
{
    return (c == '|' || c == '>' || c == '<');
}
