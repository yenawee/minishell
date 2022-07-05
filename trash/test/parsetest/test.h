#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>

#define TRUE 1
#define FALSE 0
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
	char *str;
	int type;
	struct s_token *prev;
	struct s_token *next;
} t_token;


char	*ft_strchr(const char *s, int c);
int		ft_isspace(char c);
char	*ft_strtrim(char const *s1, char const *set);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		ft_isoperator(char c);
int		ft_isalpha(int c);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_isalnum(int c);
int		ft_isdigit(int c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);
void	*ft_calloc(size_t count, size_t size);
int		check_quote_match(char *str);
char	*expand_str(char *str, t_list *env_list);
t_list	*envp_init(char **envp);
char	*find_value_in_env(char *key, t_list *env_list);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
char	*expand_env(char *str, t_list *env_list);
void	*ft_memset(void *b, int c, size_t len);
void	exec_signals();
t_token	*define_type(t_token *list);

