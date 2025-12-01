NAME = libft.a

SOURCE = ft_atoi.c ft_bzero.c ft_calloc.c \
	ft_isalnum.c ft_isalpha.c ft_isascii.c \
	ft_isdigit.c ft_isprint.c \
	ft_memchr.c ft_memcmp.c \
	ft_memcpy.c ft_itoa.c ft_memmove.c ft_memset.c \
	ft_putchar_fd.c ft_putendl_fd.c \
	ft_putnbr_fd.c ft_putstr_fd.c \
	ft_split.c ft_strchr.c ft_strdup.c \
	ft_striteri.c ft_strjoin.c \
	ft_strlcat.c ft_strlcpy.c \
	ft_strlen.c ft_strmapi.c ft_strncmp.c \
	ft_strnstr.c ft_strrchr.c \
	ft_strtrim.c ft_substr.c \
	ft_tolower.c ft_toupper.c \
	ft_print_hex.c \
	ft_printf.c \
	ft_putchar.c \
	ft_putnbr.c \
	ft_putstr.c \
	ft_print_ptr.c \
	get_next_line.c \
	get_next_line_utils.c \
	ft_strcmp.c \

OBJ = $(SOURCE:.c=.o)

CC = cc
AR = ar rcs
RM = rm -f
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

.c.o:
	@$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJ)
	@$(AR) $(NAME) $(OBJ)

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
