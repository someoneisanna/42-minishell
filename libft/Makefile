#name of the library
NAME = libft.a

#compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

#shell commands to be used
#rm: remove files or directories
#-f: ignore nonexistent files and arguments
RM = rm -f
#ar: creates/modifies/extracts from archives
#-r: insert the files member into archive (with replacement)
#-c: creates the archive
#-s: if you put that, you don't need ranlib
AR = ar -rcs

#source files
SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
		ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
		ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
		ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
		ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
		ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		ft_print_c.c ft_printf.c ft_print_n.c ft_print_p.c ft_print_s.c \
		ft_print_u.c ft_print_x.c get_next_line.c get_next_line_utils.c

#create the object files
S_OBJS = $(SRCS:.c=.o)

#bonus files
BONUS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
		ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
		ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c \
		get_next_line_bonus.c get_next_line_utils_bonus.c

#create the object (bonus) files
B_OBJS = $(BONUS:.c=.o)

#phony to make sure we can compile correctly, even
#when we have files with those names
.PHONY: all bonus clean fclean re

#first mandatory rule
all: $(NAME)

#compiles .c files into .o files provided that %.c exists or can be made
#$<: name of the first prerequisite
#$@: name of the target
%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I.

#make the library without bonus
$(NAME): $(S_OBJS)
	@$(AR) $(NAME) $(S_OBJS)

#create the library with bonus
bonus: $(S_OBJS) $(B_OBJS)
	@$(AR) $(NAME) $(S_OBJS) $(B_OBJS)

clean:
	@$(RM) $(S_OBJS) $(B_OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

#rule to use alelievr test
#so:
#	$(CC) -nostartfiles -fPIC $(CFLAGS) $(SRCS) $(BONUS)
#	gcc -nostartfiles -shared -o libft.so $(S_OBJS) $(B_OBJS)
