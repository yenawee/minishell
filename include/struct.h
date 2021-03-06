/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonjan <hyeonjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 22:03:02 by hyeonjan          #+#    #+#             */
/*   Updated: 2022/07/13 21:36:09 by hyeonjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# define S_QUOTE '\''
# define D_QUOTE '\"'
# define TRUE	1
# define FALSE 	0
# define SUCCESS 1
# define FAIL	0
# define MAX_HEREDOC 16

typedef struct s_env
{
	char	*key;
	char	*value;
}	t_env;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

enum e_type
{
	T_RRDIR,
	T_LRDIR,
	T_HEREDOC,
	T_APPEND,
	T_PIPE,
	T_AND,
	T_OR,
	T_FILE,
	T_LIMITER,
	T_WORD
};

typedef enum e_file_type
{
	FT_NOTFOUND,
	FT_DIR,
	FT_FILE
}	t_file_type;

typedef struct s_token
{
	int				type;
	char			*str;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_command {
	pid_t				pid;
	t_token				*tokens;
	char				**argv;
	int					argc;
	int					infile;
	int					outfile;
	int					token_size;
	struct s_command	*next;
}	t_command;

typedef struct s_pipeline {
	t_token				*tokens;
	int					token_size;
	int					seperated_type;
	t_command			*commands;
	struct s_pipeline	*next;
}	t_pipeline;

typedef struct s_sh
{
	t_list	*env_list;
	int		exit_status;
	int		fd_stdin;
	int		fd_stdout;
	int		fd_stderr;
	int		heredoc_index;
}	t_sh;

typedef struct s_pipes {
	int	prev_pipe[2];
	int	next_pipe[2];
}	t_pipes;

typedef enum e_pipe_fd {
	READ,
	WRITE,
}	t_pipe_fd;

#endif
