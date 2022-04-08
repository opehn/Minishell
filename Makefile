NAME = minishell
CC = gcc
FLAGS = -Wall -Wextra
# FLAGS += -g -fsanitize=address
LIBRARIES = -L$(LIBFT_DIR) -L/opt/homebrew/opt/readline/lib
INCLUDES = -I$(LIBFT_DIR) -I$(HEADER_DIR) -I/opt/homebrew/opt/readline/include

LIBFT = $(LIBFT_DIR)libft.a
LIBFT_DIR = ./libft/

HEADER_DIR	=	./includes/
HEADER_LIST	=	parsing.h \
				prompt.h \
				env.h \
				tree.h
HEADERS		=	$(addprefix $(HEADER_DIR), $(HEADER_LIST))
SRC_DIR		=	./srcs/
PARSER_DIR	=	$(SRC_DIR)parser/
ERROR_DIR	=	$(SRC_DIR)error/

# ':' Makefile이 연산하는데 재귀적인 용법을 허용하지 않는데 ":" 기호의 사용으로 그러한 재귀적인 금할 수 있다.

MAIN_SRCS	:=	prompt.c list.c
MAIN_SRCS	:=	$(addprefix $(SRC_DIR), $(MAIN_SRCS))
PARSER_SRCS	:=	parse_chk.c parsing.c parse_tree.c
PARSER_SRCS	:=	$(addprefix $(PARSER_DIR), $(PARSER_SRCS))
ERROR_SRCS	:=	error_msg.c
ERROR_SRCS	:=	$(addprefix $(ERROR_DIR), $(ERROR_SRCS))

SRCS = $(PARSER_SRCS) $(MAIN_SRCS) $(ERROR_SRCS)
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
	@rm $(OBJS)

fclean:
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm $(OBJS)
	rm $(NAME)

re : fclean all

.PHONY: all clean fclean re
