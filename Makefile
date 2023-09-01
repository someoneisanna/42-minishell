# ----------------------------------- COLORS -----------------------------------

RED = \033[0;31m
GREEN = \033[0;32m
PURPLE = \033[1;35m
RESET = \033[0m

# ---------------------------------- VARIABLES ---------------------------------

NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror
LFLAGS = -lreadline

RM = rm -f
MAKE = make --no-print-directory -C

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = srcs/main.c \
		srcs/parser.c \
		srcs/utils.c \
		srcs/tokenization/tokenizer.c \
		srcs/tokenization/tokenizer_utils.c

S_OBJS = $(SRCS:.c=.o)

# ------------------------------------ RULES -----------------------------------

.PHONY: all clean fclean re

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
