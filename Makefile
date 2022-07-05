NAME = minishell

BUILTIN_NAME = *
BUILTIN_DIR = ./builtin/
BUILTIN = $(addprefix $(BUILTIN_DIR), $(BUILTIN_NAME))

LEXER_NAME = *
LEXER_DIR = ./lexer/
LEXER = $(addprefix $(LEXER_DIR), $(LEXER_NAME))

PARSER_NAME = *
PARSER_DIR = ./parser/
PARSER = $(addprefix $(PARSER_DIR), $(PARSER_NAME))

UTILS_NAME = *
UTILS_DIR = ./utils/
UTILS = $(addprefix $(UTILS_DIR), $(UTILS_NAME))

LST_NAME = *
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
	$(CC) $(INCLUDE) $(CFLAGS) $(READLINE_FLAG) -c $< -o $@

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(READLINE_FLAG) $? -o $@
	@echo "\033[47;30m* $(NAME) was created *\033[0m"

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re :
	make fclean
	make all

.PHONY : all clean fclean re
