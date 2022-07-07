#ifndef STRUCT_H
# define STRUCT_H

# define S_QUOTE '\''
# define D_QUOTE '\"'
# define TRUE	1
# define FALSE 	0
# define SUCCESS 1
# define FAIL	0

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

typedef struct s_token
{
	int				type;
	char			*str;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_command {
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

typedef struct s_wildcard {
	char	*front_token;
	char	*rear_token;
	t_list	*middle_tokens;
	int		total_len;
}	t_wildcard;

typedef struct s_sh
{
	t_list	*env_list;
	int		exit_status;
}	t_sh;


#endif
