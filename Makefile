# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyeonjan <hyeonjan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/12 13:16:03 by yenawee           #+#    #+#              #
#    Updated: 2022/07/13 21:34:22 by hyeonjan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

BUILTIN_NAME = ft_cd.c ft_echo.c ft_env.c ft_exit.c ft_export.c ft_export_no_arg.c ft_pwd.c ft_unset.c ft_export_no_arg_2.c ft_export_one.c
BUILTIN_DIR = ./builtin/
BUILTIN = $(addprefix $(BUILTIN_DIR), $(BUILTIN_NAME))

HEREDOC_NAME = expand_in_heredoc.c heredoc.c
HEREDOC_DIR = ./heredoc/
HEREDOC = $(addprefix $(HEREDOC_DIR), $(HEREDOC_NAME))

LEXER_NAME = define_type.c expand_env.c expand_str.c find_value_in_env.c add_token.c tokenize.c
LEXER_DIR = ./lexer/
LEXER = $(addprefix $(LEXER_DIR), $(LEXER_NAME))

PARSER_NAME = make_pipelines.c test_make_pipelines.c
PARSER_DIR = ./parser/
PARSER = $(addprefix $(PARSER_DIR), $(PARSER_NAME))

UTILS_NAME = exit_msg.c ft_calloc.c ft_memset.c ft_putstr_fd.c ft_strchr.c ft_strcmp.c ft_strdup.c ft_strjoin.c ft_strlcpy.c \
			ft_strlen.c ft_strtrim.c ft_substr.c is_func.c safe_free.c ft_itoa.c ft_strlcat.c all_clear.c ft_atoi.c check_valid_env_key.c \
			get_next_line.c
UTILS_DIR = ./utils/
UTILS = $(addprefix $(UTILS_DIR), $(UTILS_NAME))

LST_NAME = ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c
LST_DIR = ./lst/
LST = $(addprefix $(LST_DIR), $(LST_NAME))

ENV_NAME = env_init.c env_list_to_char_array.c get_env_value.c
ENV_DIR = ./env/
ENV = $(addprefix $(ENV_DIR), $(ENV_NAME))

SIGNAL_NAME = exec_signals.c input_signal.c
SIGNAL_DIR = ./signal/
SIGNAL = $(addprefix $(SIGNAL_DIR), $(SIGNAL_NAME))

EXECUTOR_NAME = builtin.c check_file_type.c execute_command.c execute_pipeline.c executor.c \
				fork_execute_command.c ft_alert_safe_close.c ft_alert_safe_dup2.c handle_redirect.c \
				redirection.c two_dim_arr_clear.c wait_child.c make_cmd_argv.c make_argv_list.c expand_out_of_quote.c
EXECUTOR_DIR = ./executor/
EXECUTOR = $(addprefix $(EXECUTOR_DIR), $(EXECUTOR_NAME))

MAIN_NAME = minishell.c welcome_prompt.c
MAIN_DIR = ./
MAIN = $(addprefix $(MAIN_DIR), $(MAIN_NAME))

SRCS = $(BUILTIN) $(LEXER) $(PARSER) $(UTILS) $(LST) $(ENV) $(EXECUTOR) $(MAIN) $(HEREDOC) $(SIGNAL)

OBJS = $(SRCS:.c=.o)

INCLUDE = -Iinclude
CC = cc
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf
# READLINE_INCLUDE = -I /opt/homebrew/opt/readline/include
READLINE_INCLUDE = -I /Users/${USER}/.brew/opt/readline/include
READLINE_FLAG = -lreadline -L /Users/${USER}/.brew/opt/readline/lib
# READLINE_FLAG = -lreadline -L /opt/homebrew/opt/readline/lib
# -g -fsanitize=address
all : $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDE) $(READLINE_INCLUDE) -c $< -o $@

$(NAME) : $(OBJS)
	$(CC) $? $(CFLAGS) $(READLINE_FLAG) $(READLINE_INCLUDE) -o $@
	@echo "\033[47;30m* $(NAME) was created *\033[0m"

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

bonus : all

re :
	make fclean
	make all

.PHONY : all clean fclean re bonus
