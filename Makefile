NAME = minishell
CC = gcc
FLAGS = -Wall -Wextra -Werror
# FLAGS += -g -fsanitize=address
LIBRARIES = -L$(LIBFT_DIR) -L/opt/homebrew/opt/readline/lib
INCLUDES = -I$(LIBFT_DIR) -I$(HEADER_DIR) -I/opt/homebrew/opt/readline/include

LIBFT = $(LIBFT_DIR)libft.a
LIBFT_DIR = ./libft/

HEADER_DIR = ./includes/
HEADER_LIST = parsing.h \
				prompt.h
HEADERS = $(addprefix $(HEADER_DIR), $(HEADER_LIST))
SRC_DIR = ./srcs/
SRC_LIST = parsing.c \
			prompt.c \
			list.c \
			ft_putendl_fd.c \
			ft_strndup.c \
			ft_strlen.c
SRCS = $(addprefix $(SRC_DIR), $(SRC_LIST))

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(FLAGS) -lreadline $(LIBRARIES) $(INCLUDES) $(OBJS) -o $(NAME) 

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
