NAME = minishell
CC = gcc
FLAGS = -Wall -Wextra -g
FLAGS += -fsanitize=address
LIBRARIES = -L$(LIBFT_DIR) -L/Users/acho/.brew/opt/readline/lib
INCLUDES = -I$(LIBFT_DIR) -I$(HEADER_DIR) -I/Users/acho/.brew/opt/readline/include
LIBFT = $(LIBFT_DIR)libft.a
LIBFT_DIR = ./libft/

HEADER_DIR	=	./includes/
HEADER_LIST	=	parsing.h \
				prompt.h \
				env.h \
				tree.h \
				scanner.h \
				custom_cmd.h \
				free_data.h
HEADERS		=	$(addprefix $(HEADER_DIR), $(HEADER_LIST))
SRC_DIR		=	./srcs/
PARSER_DIR	=	$(SRC_DIR)parser/
ERROR_DIR	=	$(SRC_DIR)error/
SCANNER_DIR	=	$(SRC_DIR)scanner/
ACTION_DIR	=	$(SRC_DIR)action/
CUSTOM_DIR	=	$(SRC_DIR)custom_cmd/

# ':' Makefile이 연산하는데 재귀적인 용법을 허용하지 않는데 ":" 기호의 사용으로 그러한 재귀적인 금할 수 있다.

MAIN_SRCS		:=	prompt.c signal_handler.c free_data.c
MAIN_SRCS		:=	$(addprefix $(SRC_DIR), $(MAIN_SRCS))
PARSER_SRCS		:=	parsing.c parsing_tree.c pipe_parsing.c pipe_list_util.c pipe_parsing_util.c \
					parsing_utils.c
PARSER_SRCS		:=	$(addprefix $(PARSER_DIR), $(PARSER_SRCS))
ERROR_SRCS		:=	error_msg.c
ERROR_SRCS		:=	$(addprefix $(ERROR_DIR), $(ERROR_SRCS))
SCANNER_SRCS	:=	scanner.c scanner_util.c expand.c grow.c quot.c redirection.c
SCANNER_SRCS	:=	$(addprefix $(SCANNER_DIR), $(SCANNER_SRCS))
ACTION_SRCS		:=	action.c ft_wait.c heredoc_chk.c redir_action.c cmd_find.c split_opts.c \
					perror_action.c cmd_action.c action_utils.c
ACTION_SRCS		:=	$(addprefix $(ACTION_DIR), $(ACTION_SRCS))
CUSTOM_SRCS		:=	custom_pwd.c custom_export.c custom_unset.c custom_cd.c custom_echo.c \
					custom_exit.c custom_env.c env_util.c err_util.c
CUSTOM_SRCS		:=	$(addprefix $(CUSTOM_DIR), $(CUSTOM_SRCS))


SRCS = $(PARSER_SRCS) $(MAIN_SRCS) $(ERROR_SRCS) $(SCANNER_SRCS) $(ACTION_SRCS) $(CUSTOM_SRCS)
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(FLAGS) -lreadline $(LIBRARIES) $(INCLUDES) $(OBJS) -o $(NAME) -lft

%.o: %.c $(HEADERS)
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) all

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@rm -rf $(OBJS)

fclean:
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -rf $(OBJS)
	rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re
