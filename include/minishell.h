#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define S_QUOTE '\''
#define D_QUOTE '\"'
#define TRUE	1
#define FALSE 	0

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
	char	stack[1000];
	int		len;
}	t_stack;

typedef struct s_str
{
	char			*str;
	struct s_str	*next;
}	t_str;

enum e_type
{
	T_CMD,
	T_REDIRECT,
	T_HEREDOC,
	T_APPEND,
	T_PIPE,
	T_AND,
	T_OR,
	T_FILE,
	T_WORD
};

typedef struct s_token
{
	int				type;
	char			*str;
	struct s_token	*prev;
	struct s_token	*next;
} t_token;

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
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
void	ft_safe_free(void **p);

t_list	*envp_init(char **envp);
void 	ft_env(t_list *list);
void	ft_del(void *p);
void	ft_lst_remove_if(t_list **list, char *key);
void	ft_unset(t_list **list, char **keys);
void	ft_export_one(t_list **list, char *key, char *value, int plus_flag);
void	ft_export(t_list **list, char **str);

void	ft_pwd(t_list *env_list);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);


// new
void	safe_free(void **p);
void	exit_msg(int exit_status, int fd, char msg);
void	ft_putstr_fd(int fd, char msg);
