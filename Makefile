MAKEFLAGS += --no-print-directory
NAME       = minishell

# Main source
MAIN_SRC   = main_shell.c

# Shell sources
SHELL_SRCS = shell/shell_init.c shell/shell_command.c shell/shell_command_split.c shell/shell_command_exec.c shell/shell_loop.c shell/token_filter.c

# Parsing sources
PARSE_SRCS = parsing/parsing/parsing.c parsing/parsing/parsing2.c \
             parsing/parsing/aux_parsing.c parsing/parsing/parse_quotes.c \
             parsing/parsing/free_and_exit.c parsing/parsing/free_and_exit2.c \
             parsing/parsing/ft_lst.c parsing/parsing/ft_lst2.c \
             parsing/parsing/redir.c parsing/parsing/redir_utils.c \
             parsing/parsing/remove_quotes.c \
             parsing/parsing/quote_utils.c \
             parsing/parsing/quote_utils_aux.c \
             parsing/parsing/check_list.c parsing/parsing/parsing_helpers.c \
             parsing/parsing/parsing_split.c \
             parsing/parsing/parsing_utils.c \
             parsing/expander/expand_variable.c parsing/expander/expand_helpers.c \
             parsing/expander/expand_varname.c \
             parsing/expander/expand_quotes.c parsing/expander/expand_quotes_aux.c \
             parsing/expander/expand_quotes_escape.c \
             parsing/expander/expand_aux.c \
             parsing/expander/expand_aux2.c \
             parsing/lexer/lexer.c parsing/lexer/validate_cmd.c \
             parsing/env_cpy/new_env.c parsing/env_cpy/new_env2.c \
             parsing/signals/signal_handler.c

# Execution sources - using normed versions
EXEC_SRCS  = exec/srcs/builtins.c exec/srcs/builtins2.c exec/srcs/cleanup.c \
             exec/srcs/env_helper.c exec/srcs/error_utils.c exec/srcs/exec.c \
             exec/srcs/helper_builtins.c exec/srcs/helper.c exec/srcs/pipes.c \
             exec/srcs/redirection.c exec/srcs/builtins_cd.c exec/srcs/builtins_echo.c \
             exec/srcs/builtins_echo_aux.c exec/srcs/builtins_export.c exec/srcs/builtins_unset.c \
             exec/srcs/builtins_helpers.c exec/srcs/builtins_helpers2.c \
             exec/srcs/builtins_cd_utils.c exec/srcs/exec_builtins.c \
             exec/srcs/exec_command_utils.c exec/srcs/exec_path_utils.c \
             exec/srcs/exec_utils.c exec/srcs/glob_expansion_core.c \
             exec/srcs/glob_expansion_utils.c exec/srcs/glob_expansion.c \
             exec/srcs/glob_helpers.c exec/srcs/glob_pattern.c exec/srcs/glob_utils.c \
             exec/srcs/pipe_process.c exec/srcs/pipe_utils.c exec/srcs/pipe_cleanup.c \
             exec/srcs/redirect_handlers.c exec/srcs/redirect_io.c \
             exec/srcs/shell_env_utils.c exec/srcs/shell_env.c \
             exec/srcs/shell_token_utils.c exec/srcs/token_utils.c \
             exec/srcs/heredoc_handler.c exec/srcs/heredoc_aux.c \
             exec/srcs/shell_env_aux.c

# Combine all sources
SRC        = $(MAIN_SRC) $(SHELL_SRCS) $(PARSE_SRCS) $(EXEC_SRCS)
OBJ        = $(SRC:.c=.o)

LIBFT_DIR  = libft
LIBFT_A    = $(LIBFT_DIR)/libft.a
CFLAGS     = -Wall -Wextra -Werror -I. -I$(LIBFT_DIR) -g -fPIE
LDFLAGS    = -lreadline -pie

# Cores
GREEN  = \033[0;32m
BLUE   = \033[0;34m
YELLOW = \033[0;33m
RESET  = \033[0m

all: $(NAME)

$(LIBFT_A):
	@echo -e "$(YELLOW)Building libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(LIBFT_A) $(OBJ)
	@echo -e "$(BLUE)Compiling Minishell...$(RESET)"
	@$(CC) $(OBJ) $(LIBFT_A) $(LDFLAGS) -o $@
	@echo -e "$(GREEN)Minishell compiled successfully! ✅$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo -e "$(BLUE)Object files cleaned$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo -e "$(BLUE)Executable cleaned$(RESET)"

re: fclean all

va: $(NAME)
	@valgrind --suppressions=readline.supp --leak-check=full --track-fds=no --show-leak-kinds=all --child-silent-after-fork=yes --trace-children=no ./$(NAME)

.PHONY: all clean fclean re norm
