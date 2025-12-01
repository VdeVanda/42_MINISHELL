NAME = minishell
CC = cc -g
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -I. -Ilibft
READLINE = -lreadline -lncurses

LIBFT = libft/libft.a

PARSING = parsing/
EXPANDER = expander/
LEXER = lexer/


SRC = test_parser.c $(SRC_ENV_CPY) $(PARSING)aux_parsing.c $(PARSING)ft_lst.c $(PARSING)free_and_exit.c $(PARSING)ft_lst2.c $(PARSING)redir.c $(PARSING)redir_utils.c $(PARSING)parsing.c $(PARSING)parsing2.c $(PARSING)parse_quotes.c $(PARSING)free_and_exit2.c $(PARSING)remove_quotes.c $(PARSING)quote_utils.c $(PARSING)check_list.c signals/signal_handler.c $(EXPANDER)expand_variable.c $(EXPANDER)expand_aux.c $(EXPANDER)expand_aux2.c $(LEXER)lexer.c $(LEXER)validate_cmd.c

SRC_ENV_CPY = env_cpy/new_env.c env_cpy/new_env2.c

OBJ = $(SRC:.c=.o)

GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
RESET = \033[0m

all: $(NAME)

$(LIBFT):
	@echo "${YELLOW}Compiling libft...${RESET}"
	@make -s -C ./libft

$(NAME): $(OBJ) $(LIBFT)
	@echo "${YELLOW}Linking object files and libraries...${RESET}"
	@${CC} ${CFLAGS} ${OBJ} $(LIBFT) -o $(NAME) ${READLINE}
	@echo "${GREEN}$(NAME) created successfully.${RESET}"

%.o: %.c
	@echo "${YELLOW}Compiling $<...${RESET}"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "${RED}Cleaning object files...${RESET}"
	@$(RM) $(OBJ)
	@make clean -s -C ./libft

fclean: clean
	@echo "${RED}Deleting executable and libraries...${RESET}"
	@$(RM) $(NAME)
	@$(RM) $(LIBFT)
	@echo "${RED}$(NAME) deleted successfully.${RESET}"

re: fclean all

run: all
	@./$(NAME)

r:
	make re && clear && ./minishell

va: $(NAME)
	@valgrind --suppressions=readline.supp --leak-check=full --track-fds=yes --show-leak-kinds=all ./$(NAME)

v: all
	@valgrind ./$(NAME)

.PHONY: all, clean, fclean, re, run, va, v
