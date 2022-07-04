#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>

#define S_QUOTE '\''
#define D_QUOTE '\"'
#define TRUE	1
#define FALSE 	0
#define SUCCESS 1
#define FAIL	0

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
	int				type;
	char			*str;
	struct s_token	*prev;
	struct s_token	*next;
} t_token;

typedef struct s_command {
	t_token				*tokens; /* 토큰 !!!!!*/
	int					token_size;
	struct s_command	*next;
}	t_command;

typedef struct s_pipeline {
	t_token				*tokens; /* 토큰 !!!!!*/
	int					token_size;
	int					seperated_type;
	t_command			*commands;
	struct s_pipeline	*next;

}	t_pipeline;

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
int		ft_env(t_list *list);
void	ft_del(void *p);
void	ft_lst_remove_if(t_list **list, char *key);
int		ft_unset(t_list **list, char **keys);
void	ft_export_one(t_list **list, char *key, char *value, int plus_flag);
int		ft_export(t_list **list, char **str);
int		ft_export_no_arg(t_list *env_list);

int		ft_pwd(void);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		is_valid_key_first(char c);
int		is_valid_key_last(char c);



// new
void	safe_free(void **p);
void	exit_msg(int exit_status, int fd, char *msg);
void	ft_putstr_fd(int fd, char *msg);
char	*ft_strtrim(char const *s1, char const *set);
int		ft_isspace(char c);
int		ft_isoperator(char c);
char	*expand_str(char *str, t_list *env_list);
t_list	*envp_init(char **envp);
char	*find_value_in_env(char *key, t_list *env_list);
char	*expand_env(char *str, t_list *env_list);
void	exec_signals();
t_token	*define_type(t_token *list);
int		parse(t_token **list, char *line, t_list *env_list);
void	*ft_alert_calloc(size_t count, size_t size);
int		make_pipelines(t_pipeline **pipelines, t_token *tokens);