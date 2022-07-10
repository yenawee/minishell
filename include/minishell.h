/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenawee <yenawee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 22:13:34 by hyeonjan          #+#    #+#             */
/*   Updated: 2022/07/10 18:11:24 by hyeonjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/stat.h>

# include "struct.h"

//lst
void	ft_lstadd_back(t_list	**head, t_list *new);
void	ft_lstadd_front(t_list	**head, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
int		ft_lstsize(t_list *lst);
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_alert_lstnew(void *content);

//utils
char	*ft_strchr(const char *str, int c);
char	*ft_strdup(const char *s1);
void	*ft_calloc(size_t count, size_t size);
void	*ft_alert_calloc(size_t count, size_t size);
void	*ft_memset(void *b, int c, size_t len);
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
void	ft_safe_free(void **p);
void	ft_putstr_fd(int fd, char *msg);
char	*ft_strtrim(char const *s1, char const *set);
int		ft_isspace(char c);
int		ft_isoperator(char c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		is_valid_key_first(char c);
int		is_valid_key_last(char c);
int		check_valid_key(char *key);
char	*ft_alert_strdup(const char *s1);
char	*ft_alert_strjoin(char const *s1, char const *s2);
void	ft_alert_str_append(char **prev, char *added);
void	ft_safe_strjoin(char **ret, char *str);
char	*ft_itoa(int n);
void	all_clear(char **input, char **trimed, \
				t_pipeline **list, t_token **tokens);
int		ft_atoi(const char *str);
void	exit_msg(int exit_status, int fd, char *msg);

//builtin
int		ft_unset(t_list **list, char **keys);
void	ft_export_one(t_list **list, char *key, char *value, int plus_flag);
int		ft_export(t_list **list, char **str);
int		ft_export_no_arg(t_list *env_list);
void	_export_print(t_env *ret);
int		ft_pwd(void);
int		ft_env(t_list *list);
int		ft_echo(char **argv);
int		ft_exit(t_sh *sh, int argc, char **argv);

//env
t_list	*envp_init(char **envp);
char	**env_list_to_char_arr(t_list *env_list);
char	*get_env_value(t_list *env_list, char *key);
char	*_get_env_value_without_malloc(t_list *env_list, char *key);

//signal
void	exec_signals(void);
void	set_input_signal(void);

//wildcard
t_wildcard	*str_to_t_wildcard(char *str);
int			is_matched(char *file_name, t_wildcard *wildcard);
void		match_wildcard(char **file_names, int file_count, \
						t_wildcard **wildcards, int wildcard_count);

//lexer
int		parse(t_token **list, char *line, t_list *env_list);
void	addtoken(t_token **list, char *begin, char *end, t_list *env_list);
char	*expand_str(char *str, t_sh *sh);
char	*expand_env(char *str, t_sh *sh);
char	*find_value_in_env(char *key, t_list *env_list);
t_token	*define_type(t_token *list);

//parser
int		make_pipelines(t_pipeline **pipelines, t_token *tokens);

//heredoc
char	*expand_in_heredoc(char *input, int fd, t_list *env_list);
int		handle_heredoc(t_token *tokens, t_list *env_list);

//execve
void	make_cmd_argv(t_command *cmd, t_sh *sh);

//excutor
int		check_ftype(char *cmd);
int		is_builtin(t_command *command);
int		execute_builtin(t_sh *sh, t_command *command);
void	execute_input(t_sh *sh, t_pipeline *list);
char	*ft_alert_join_path(char *path, char *cmd);
int		search_execve(t_sh *sh, t_command *command, char *envp);
void	execute_simple_cmd(t_sh *sh, t_command *command, char **envp);
int		handle_redirect(t_sh *sh, t_command *command);
void	two_dim_arr_clear(char **two_dim_arr);
int		wait_child(pid_t pid);
int		wait_childs(t_pipeline *pipeline);
int		execute_pipeline(t_sh *sh, t_pipeline *pipeline, char **envp);
void	fork_execute_command(t_sh *sh, t_pipes *p, t_command *command, \
							char **envp);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
void	ft_alert_safe_close(int *fd);
void	ft_alert_safe_dup2(t_sh *sh, int fd, int to_fd);
void	test_list(t_pipeline *list);
int		redir_in(char *file_name);
int		redir_out(char *file_name);
int		redir_append(char *file_name);
int		redir_heredoc(t_sh *sh);

#endif
