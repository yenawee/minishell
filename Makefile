NAME = minishell

BUILTIN_NAME = ft_cd.c ft_echo.c ft_env.c ft_exit.c ft_export.c ft_export_no_arg.c ft_pwd.c
BUILTIN_DIR = ./builtin/
BUILTIN = $(addprefix $(BUILTIN_DIR), $(BUILTIN_NAME))

LEXER_NAME = define_type.c expand_env.c expand_str.c find_value_in_env.c tokenizer.c
LEXER_DIR = ./lexer/
LEXER = $(addprefix $(LEXER_DIR), $(LEXER_NAME))

PARSER_NAME = make_pipelines.c test_make_pipelines.c
PARSER_DIR = ./parser/
PARSER = $(addprefix $(PARSER_DIR), $(PARSER_NAME))

UTILS_NAME = env_init.c exit_msg.c ft_calloc.c ft_memset.c ft_putstr_fd.c ft_strchr.c ft_strcmp.c ft_strdup.c ft_strjoin.c ft_strlcpy.c \
			ft_strlen.c ft_strtrim.c ft_substr.c is_func.c safe_free.c
UTILS_DIR = ./utils/
UTILS = $(addprefix $(UTILS_DIR), $(UTILS_NAME))

LST_NAME = ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c
LST_DIR = ./lst/
LST = $(addprefix $(LST_DIR), $(LST_NAME))

MAIN_NAME = minishell.c
MAIN_DIR = ./
MAIN = $(addprefix $(MAIN_DIR), $(MAIN_NAME))

SRCS = $(BUILTIN) $(LEXER) $(PARSER) $(UTILS) $(LST) $(MAIN)
OBJS = $(SRCS:.c=.o)

INCLUDE = -Iinclude
CC = cc
# CFLAGS = -Wall -Werror -Wextra
RM = rm -rf
READLINE_FLAG = -lreadline -L /Users/${USER}/.brew/opt/readline/lib -I /Users/${USER}/.brew/opt/readline/include

all : $(NAME)

%.o : %.c
	@$(CC) $(INCLUDE) $(READLINE_FLAG) -w -c $< -o $@

$(NAME) : $(OBJS)
	$(CC) $(READLINE_FLAG) $? -o $@
	@echo "\033[47;30m* $(NAME) was created *\033[0m"

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re :
	make fclean
	make all

.PHONY : all clean fclean re
