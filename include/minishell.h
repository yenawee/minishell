#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct	s_stack
{
	char    stack[1000];
	int     len;
}   t_stack;

typedef struct s_str
{
    char *str;
    struct s_str *next;
} t_str;