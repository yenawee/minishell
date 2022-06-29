#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

char	*ft_strchr(const char *s, int c);
int ft_isspace(char c);
char	*ft_strtrim(char const *s1, char const *set);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int ft_isoperator(char c);
int check_quote_match(char *str);

typedef struct s_token
{
    char *str;
    int type;
    struct s_token *prev;
    struct s_token *next;
} t_token;
