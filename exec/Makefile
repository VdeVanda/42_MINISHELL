NAME       = minishell
SRC        = srcs/shell.c srcs/redirection.c srcs/helper_builtins.c srcs/pipes.c \
           srcs/builtins.c srcs/env_helper.c srcs/builtins2.c srcs/exec.c \
           srcs/cleanup.c srcs/helper.c srcs/glob_utils.c srcs/glob_pattern.c \
           srcs/shell_env.c srcs/token_utils.c srcs/exec_utils.c \
           srcs/exec_builtins.c srcs/error_utils.c srcs/shell_env_utils.c \
           srcs/shell_token_utils.c srcs/glob_expansion.c srcs/builtins_helpers.c \
           srcs/pipe_utils.c srcs/pipe_process.c srcs/redirect_handlers.c \
           srcs/redirect_io.c srcs/builtins_helpers2.c srcs/builtins_unset.c \
           srcs/exec_path_utils.c srcs/glob_expansion_utils.c \
           srcs/builtins_cd_utils.c srcs/glob_expansion_core.c srcs/heredoc_handler.c

# Object directory and files
OBJ_DIR    = obj
OBJ        = $(SRC:srcs/%.c=$(OBJ_DIR)/%.o)

LIBFT_DIR  = libft
LIBFT_A    = $(LIBFT_DIR)/libft.a
CFLAGS    += -I$(LIBFT_DIR)

LDFLAGS    = -lreadline   # adiciona aqui a flag para readline

# Cores
GREEN  = \033[0;32m
BLUE   = \033[0;34m
RESET  = \033[0m

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_A)
	@echo "$(BLUE)Compiling Minishell...$(RESET)" 
	@$(CC) $(OBJ) $(LIBFT_A) $(LDFLAGS) -o $@    # linka com -lreadline aqui
	@echo "$(GREEN)Finished ✅$(RESET)"

# Create object directory and compile .c files
$(OBJ_DIR)/%.o: srcs/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@   # silencia a compilação dos .c

# Create object directory if it doesn't exist
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT_A):
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	@$(RM) -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "$(BLUE)Cleaned object files$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "$(BLUE)Removed binary$(RESET)"

re: fclean all

.PHONY: all clean fclean re