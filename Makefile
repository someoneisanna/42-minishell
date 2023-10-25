# ----------------------------------- COLORS -----------------------------------

RED = \033[0;31m
GREEN = \033[0;32m
PURPLE = \033[1;35m
RESET = \033[0m

# ---------------------------------- VARIABLES ---------------------------------

NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
LFLAGS = -lreadline

RM = rm -f
MAKE = make --no-print-directory -C

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = srcs/main.c \
		srcs/parsing/parser.c \
		srcs/parsing/tokenizer.c \
		srcs/parsing/tokenizer_utils.c \
		srcs/parsing/syntax_checker.c \
		srcs/parsing/expander.c \
		srcs/parsing/command_table.c \
		srcs/parsing/command_table_utils.c \
		srcs/environment/environment_lst.c \
		srcs/execution/executer.c \
		srcs/execution/redir_handler.c \
		srcs/execution/pipes_handler.c \
		srcs/builtins/cd.c \
		srcs/builtins/echo.c \
		srcs/builtins/env.c \
		srcs/builtins/exit.c \
		srcs/builtins/export.c \
		srcs/builtins/pwd.c \
		srcs/builtins/unset.c \
		srcs/utils/main_utils.c \
		srcs/utils/parsing_utils.c \
		srcs/utils/execution_utils.c \
		srcs/utils/free_utils.c \

S_OBJS = $(SRCS:.c=.o)

# ------------------------------------ RULES -----------------------------------

all: $(NAME)

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I.
	@printf "$(PURPLE)	Compiled$(RESET) $<\n"

$(NAME): $(S_OBJS)
	@$(MAKE) $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(SRCS) $(LIBFT) $(LFLAGS) -o $(NAME)
	@printf "$(GREEN)	Executable ./$(NAME) was created.\n$(RESET)"

clean:
	@$(MAKE) $(LIBFT_DIR) clean
	@$(RM) $(S_OBJS)
	@printf "$(RED)	Object files were removed.\n$(RESET)"

fclean: clean
	@$(MAKE) $(LIBFT_DIR) fclean
	@$(RM) $(NAME)
	@printf "$(RED)	Executable ./$(NAME) was removed.\n$(RESET)"

re: fclean all

valgrind: all
	@valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)

.PHONY: all clean fclean re
