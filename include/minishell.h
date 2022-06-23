#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define S_QUOTE '\''
#define D_QUOTE '\"'

typedef struct s_env
{
	char	*key;
	char	*value;
} t_env;

typedef struct	s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;
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

void	*ft_calloc(size_t count, size_t size);
void	ft_lstadd_back(t_list	**head, t_list *new);
void	ft_lstadd_front(t_list	**head, t_list *new);
void 	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
int		ft_lstsize(t_list *lst);
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

char	*ft_strchr(const char *str, int c);
char	*ft_strdup(const char *s1);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memset(void *b, int c, size_t len);
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_safe_free(void **p);