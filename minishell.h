/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 22:57:07 by vabatist          #+#    #+#             */
/*   Updated: 2025/11/19 11:47:15 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define EXIT_NORMAL 42
# define EXIT_WITH_CODE 43

extern volatile sig_atomic_t	g_signal_status;

/**
 * @brief Represents the type of token or operation in a shell command.
 *
 * This enum is used to categorize different types of tokens in a shell command,
 * such as simple commands, pipes, input/output redirections,
	and here-documents.
 * It helps in parsing and executing shell commands by providing a clear
 * distinction between different operations and their associated behaviors.
 *
 * The types include:
 * - SIMPLE: A simple command without any special operators
 * - PIPE: A command that is part of a pipeline, connecting the output
 *   of one command to the input of another
 * - REDIR_IN: Input redirection from a file
 * - REDIR_OUT: Output redirection to a file
 * - REDIR_OUT_APPND: Output redirection to a file with append mode
 * - HERE_DOC: A here-document, which allows for multi-line input redirection
 * - HERE_DOC_DONE: Indicates the end of a here-document
 * - ERROR: Represents an error condition in parsing or execution
 */
typedef enum e_type
{
	SIMPLE = 0,
	PIPE = 1,
	REDIR_IN = 2,
	REDIR_OUT = 3,
	REDIR_OUT_APPND = 4,
	HERE_DOC = 5,
	HERE_DOC_DONE = 6,
	AND_OP = 7,
	ERROR = 8,
	REDIR_OUT_FORCE = 9
}								t_type;

/**
 * @brief Represents different signal handling modes in the shell.
 * This enum is used to specify how the shell should handle signals
 * in various contexts, such as the parent process, child processes,
 * and during here-document input.
 * @note The specific signal handling behavior for each mode
 *  is defined elsewhere in the signal handling implementation.
 * @param PARENT Mode for the main shell process
 * @param CHILD Mode for child processes executing commands
 * @param HEREDOC Mode for handling signals during here-document input
 * @param PARENT_WAIT Mode for the parent process while waiting
 * for child processes to complete
 */
typedef enum e_sigs
{
	PARENT = 0,
	CHILD = 1,
	HEREDOC = 2,
	PARENT_WAIT = 3
}								t_sigs;

/**
 * @brief Stores file descriptors for input/output and their saved states.
 *

 * This structure is used to manage input/output operations
 * in a shell environment.

 * It allows the shell to handle redirections and restore original
 * file descriptors after executing commands,
 * ensuring proper input/output handling during command execution.
 *
 * @param fd_in File descriptor for input redirection
 * @param fd_out File descriptor for output redirection
 * @param saved_stdin Saved state of standard input (stdin)
 * @param saved_stdout Saved state of standard output (stdout)
 */
typedef struct s_io
{
	int							fd_in;
	int							fd_out;
	int							saved_stdin;
	int							saved_stdout;
}								t_io;

typedef struct s_pipe_data
{
	int							prev_fd;
	int							*pipe_fd;
	int							has_next;
	char						**envp;
}								t_pipe_data;

typedef struct s_match_data
{
	char						**matches;
	int							count;
	int							capacity;
}								t_match_data;

/**
 * @brief Represents a single redirection (filename and type).
 *
 * This structure is used to manage input/output redirections in shell commands.
 * It forms a linked list of redirections for a single command.
 *
 * @param filename The name of the file for redirection
 * @param type The type of redirection (input, output, append, here-doc)
 * @param next Pointer to the next redirection in the linked list
 */
typedef struct s_redir
{
	char						*filename;
	t_type						type;
	int							quoted_delimiter;
	struct s_redir				*next;
}								t_redir;

/**
 * @brief Represents a parsed command or pipeline segment.
 *
 * This structure is essential for managing the execution flow of commands
 * in a shell environment. It contains all necessary information about a command
 * including its arguments, type, redirections, IO info, process IDs, and links
 * to the next token.
 *
 * @param token Array of strings representing the command and its arguments
 * @param is_builtin Flag indicating if the command is a built-in shell command
 * @param type The type of command (e.g., simple command, pipe, redirection)
 * @param here_doc Flag indicating if this token is part of a here-document
 * @param redir Linked list of redirections associated with this command
 * @param io Structure holding file descriptors for input/output operations
 * @param fd Array of two integers for pipe file descriptors
 * @param pid The process ID of the command
 * @param heredoc_fd Array of two integers for here-document file descriptors
 * @param next Pointer to the next token in the linked list
 */
typedef struct s_tokens
{
	char						**token;
	int							is_builtin;
	t_type						type;
	int							here_doc;
	t_redir						*redir;
	t_io						io;
	int							fd[2];
	pid_t						pid;
	int							heredoc_fd[2];
	struct s_tokens				*next;
}								t_tokens;

/**
 * @brief Represents an environment variable with its name, value,
	and visibility.
 *

 * This structure is used to manage env variables in a shell environment.
 * It allows the shell to store, retrieve, and manipulate environment variables
 * dynamically through a linked list structure.
 *
 * @param var The name of the environment variable
 * @param value The value of the environment variable

 * @param visible Flag indicating if the variable is visible
 * in the current shell context
 * @param next Pointer to the next environment variable in the linked list
 */
typedef struct s_envc
{
	char						*var;
	char						*value;
	int							visible;
	struct s_envc				*next;
}								t_envc;

/**
 * @brief Represents the shell environment.
 *
 * This structure is the core of the shell, managing its state and operations.
 * It includes tokens, a 2D array of strings, command status, environment
 * variables, and an array of environment variables.
 *

 * @param tokens A linked list of parsed tokens representing
 * commands and their arguments
 * @param arr_2d A 2D array of strings for command arguments

 * @param command_status An integer representing the status of the
 * last executed command
 * @param env A linked list of environment variables

 * @param env_arr An array of strings representing the environment
 * variables for use in commands
 *
 * It allows the shell to execute commands, manage environment variables,
 * and maintain the overall state of the shell session.
 */
typedef struct s_shell
{
	t_tokens					*tokens;
	char						**arr_2d;
	int							command_status;
	int							has_and_operator;
	t_envc						*env;
	char						**env_arr;
}								t_shell;

/**
 * @brief Function prototypes for the shell environment.
 *
 * These functions are used to manage the shell's state,
 * including parsing input, handling tokens, and managing environment variables.
 */

// *************** PARSING ***************

/* parsing/parsing.c */
void							parse_input(char *cmd);

/* parsing/parsing_helpers.c */
char							*handle_quotes_and_redir(char *replaced,
									char **cmd);
char							*handle_special_chars(char *replaced,
									char **cmd);
int								check_input(char c, char **replaced);

/* parsing/parsing_split.c */
char							**smart_split_spaces(char *str);
void							split_spaces(void);

/* parsing/parsing_utils.c */
char							*replace_chars(char *cmd, char *replaced,
									char *temp);
char							*process_input_chars(char *cmd);
void							split_spaces(void);
int								check_input(char c, char **replaced);
char							*replace_chars(char *cmd, char *replaced,
									char *temp);

/* parsing/parsing2.c */
int								check_input_aux(char *replaced);
void							populate_lst(char **arr_split);
char							*add_char(char *str, char c);
int								closed_quotes(char *cmd);

/* parsing/aux_parsing.c */
int								is_whitespace(char c);
int								count_tokens(char **arr_split);
int								check_builtin(char *token);

/* parsing/free_and_exit.c */
void							ft_free(void);
void							free_lst(void);
void							ft_free_err(char **arr, char *err);
void							free_redir(t_redir **redir);
void							parsing_error(char *parsed);

/* parsing/free_and_exit2.c */
void							free_arr2(char **arr);

/* parsing/ft_lst.c */
t_tokens						*ft_lsttoken(char **args);
t_tokens						*ft_tokenslast(t_tokens *tokens);
void							ft_tokensadd_front(t_tokens **tokens,
									t_tokens *node);
void							ft_tokensadd_back(t_tokens **tokens,
									t_tokens *node);
t_shell							*get_shell(void);

/* parsing/ft_lst2.c */
t_redir							*lst_redir(void);
void							ft_lstadd_back_redir(t_redir **lst,
									t_redir *new);

/* parsing/redir.c */
void							populate_redir(char **arr, t_tokens *lsttokens,
									int type);
char							*parse_redir(char *replaced, char **cmd);

/* parsing/redir_utils.c */
int								get_redir_len(char *tok);
int								get_type(char *tok);

/* parsing/parse_quotes.c */
char							*parse_quotes(char *replaced, char **cmd);

/* parsing/remove_quotes.c.c */
void							check_quotes_tokens(void);
void							check_quotes_redir(t_tokens *tokens);

/* parsing/quote_utils.c */
void							handle_escape_sequence(char *token, int *i,
									char *new, int *j);
void							process_quote_char(char *token, int *i,
									char *q);
char							*ft_strdup_q(char *token);

/* parsing/quote_utils_aux.c */
char							*copy_between_quotes(char *token, char *new,
									int len);
char							*copy_entire_token(char *token, char *new,
									int len);

/* parsing/check_list.c */
void							check_list(void);

// *************** EXPANDER ***************

/* expander/expand_variable.c */
char							*expand_token(char *token);

/* expander/expand_helpers.c */
char							*add_char_to_result(char *result, char c);
char							*expand_at_position(char *token, int *i,
									char *result);
char							*extract_variable_name(char *token, int *i,
									int *is_braced);

/* expander/expand_quotes.c */
char							*expand_token_with_quotes(char *token,
									char *result);
char							*process_char_in_token(char *token, int *i,
									char *result, int *quotes);

/* expander/expand_quotes_aux.c */
char							*handle_quote_chars(char *token, int *i,
									int *quotes, char *result);
char							*handle_escape_logic(char *token, int *i,
									char *result, int *quotes);
char							*handle_variable_logic(char *token, int *i,
									char *result, int *quotes);

/* expander/expand_quotes_escape.c */
char							*handle_unquoted_escape(char *token, int *i,
									char *result);
char							*handle_escape_sequences(char *token, int *i,
									char *result);
char							*handle_escaped_char(char *result, char c,
									int *i);
char							*handle_variable_expansion(char *token, int *i,
									char *result);

/* expander/expand_aux.c */
void							expand_tokens(void);
char							*ft_get_env(char *var);
int								in_single_quotes(char *str);
char							*trim_spaces(char *result, char **final,
									int *i);
char							*parse_status(void);

/* expander/expand_aux2.c */
int								check_ws(char *exp);
char							**recreate_tokens(int i, int count, char **tok,
									char *exp);
int								special_char(char c);

// *************** LEXER ***************

/* lexer/lexer.c */
int								is_special_char(char c);
bool							has_text(char *cmd_line);
bool							check_syntax(char *cmd);

/* lexer/validate_cmd.c */
bool							validate_cmd(char *cmd_line, int len,
									bool char_found, bool quotes);

// *************** NEW ENV ***************

/* env_cpy/new_env.c */
void							ft_lstadd_back_env(t_envc **env_new, char *env);
t_envc							*ft_env_cpy(char **env, t_envc *env_new);

/* env_cpy/new_env2.c */
void							ft_lstclear_env(t_envc **env_new);
void							print_env_list(t_envc *env);

// *************** SIGNALS ***************

/* signals/signal_handler.c */
void							handle_sig(t_sigs mode);

// *************** EXECUTION ***************

// Function prototypes for execution
char							*get_command_path(char *cmd);

// exec
void							process_commands(t_tokens *tokens,
									char **my_envp);
int								execute_command(t_tokens *token,
									char **my_envp);
char							**execute_builtin(char **av, char **my_envp,
									int *status);

// exec_utils.c
char							*check_absolute_path(char *cmd);
char							*build_path(char *dir, char *cmd);
int								setup_io_redirections(t_tokens *token);
int								fork_and_execute(char *cmd_path,
									char **expanded_tokens, char **my_envp);
char							**get_path_dirs(void);

// exec_path_utils.c
char							*search_in_path_dirs(char **path_dirs,
									char *cmd);

// exec_command_utils.c
char							**prepare_expanded_tokens(t_tokens *token);
int								handle_redirection_setup(t_tokens *token,
									char **expanded_tokens);
void							cleanup_execution(t_tokens *token,
									char **expanded_tokens);
int								execute_builtin_command(char **expanded_tokens,
									char **my_envp);
int								execute_external_command(char **expanded_tokens,
									char **my_envp);

// exec_builtins.c
char							**dispatch_builtin(char **av, char **my_envp,
									int *status);
char							**handle_export_builtin(char **av,
									char **my_envp, int *status);

// builtins
int								is_builtin(char *cmd);
int								is_valid_name(char *name);
int								find_env_index(char **envp, char *name);
char							*create_env_string(char *name, char *value);
int								count_env(char **envp);
char							**add_new_var(char **envp, char *name,
									char *value);
int								pwd_builtin(void);
int								echo_builtin(char **av);
int								is_n_flag(char *str);
int								is_e_flag(char *str);

// builtins_echo_aux.c
void							print_with_escapes(char *str);
int								process_echo_flags(char **av, int *newline,
									int *escape_mode);
void							print_echo_args(char **av, int start_index,
									int escape_mode);
int								cd_builtin(char **av);
int								env_builtin(char **envp);
int								print_export(char **envp);
char							**export_builtin(char **envp, char **argv);
char							**unset_builtin(char **av, char **envp);
int								exit_builtin(char **av);

// CD utilities
char							*expand_tilde_path(char *path);
char							*handle_dash_argument(void);
void							free_path_if_needed(char *path, char **av);
char							*get_cd_path(char **av);
int								handle_cd_error(char **av, int result);

// builtin helpers - some functions are static in builtins.c
char							*extract_var_name(char *arg);
char							*reconstruct_var_value(char **argv);
char							**process_single_export(char **envp, char *arg);
char							**update_environment(char **envp, char *name,
									char *value);
void							print_export_error(char *arg);
void							print_export_no_value_error(char *arg);

// exec helpers - functions are static in exec.c

// main helpers - functions are static in main_shell.c

// cleanup
void							free_split(char **split);
void							free_tokens(t_tokens *head);
void							free_environment(char **envp);

// Helper functions
char							**copy_environment(char **envp);
void							setup_signals(void);

// Error handling
void							print_error(char *cmd, char *arg, char *msg);
void							print_command_error(char *cmd, int error_code);

// pipes
int								handle_pipe(t_tokens *tokens, char **envp);
int								contains_pipe(t_tokens *token);

// pipe_utils.c
void							setup_pipe_io(int prev_fd, int *pipe_fd,
									int has_next);
void							execute_child_command(t_tokens *current,
									char **envp);
void							manage_pipe_fds(int *prev_fd, int *pipe_fd,
									int has_next);

// pipe_cleanup.c
void							cleanup_child_inherited_memory(void);

// pipe_process.c
int								handle_child_process(t_tokens *current,
									int prev_fd, int *pipe_fd, char **envp);
int								wait_for_children(t_tokens *tokens);

// redirect
int								handle_redirect(t_tokens *token,
									char **my_envp);
int								setup_redirections(t_redir *redir);
int								restore_io(t_io *io);

// redirect_handlers.c
int								handle_input_redirect(char *filename);
int								handle_output_redirect(char *filename);
int								handle_append_redirect(char *filename);
int								handle_heredoc_redirect(void);
int								process_heredoc(char *delimiter, int pipe_fd[2],
									int quoted_delimiter);

// heredoc_aux.c
char							*process_heredoc_line(char *content, char *line,
									int expand_vars);
int								should_continue_heredoc(char *line,
									char *delimiter);
int								check_signal_during_readline(void);
char							*handle_heredoc_loop(char *content,
									char *delimiter, int quoted_delimiter);
int								write_heredoc_to_pipe(char *content,
									int pipe_fd[2]);

// redirect_io.c
int								setup_io_backup(t_io *io);

// Environment management
t_envc							*init_env(char **envp);
char							**env_to_array(t_envc *env);
void							free_env_list(t_envc *env);

// shell_env_utils.c
int								count_visible_env(t_envc *env);
char							*create_env_from_node(t_envc *env_node);
t_envc							*create_env_node(char *env_str);
void							add_env_node_to_list(t_envc **env_list,
									t_envc *new_node);

// shell_token_utils.c
void							free_tokens(t_tokens *head);
void							free_redirections(t_redir *redir);

// token filter
void							remove_empty_unquoted_tokens(void);

// Glob expansion
int								has_wildcards(const char *str);
char							**expand_globs(char **tokens);
int								match_pattern(const char *pattern,
									const char *string);
char							**expand_wildcard(const char *pattern);
char							**process_token(char **result,
									int *result_count, char *token);

// Glob utilities
void							cleanup_matches(char **matches, int count);
char							**resize_matches_array(char **matches,
									int *capacity);
int								add_match_to_array(char ***matches, int *count,
									int *capacity, const char *name);
char							**handle_no_matches(const char *pattern);
void							free_expanded_array(char **expanded);
char							**add_expanded_matches(char **result,
									int *result_count, char **expanded);
char							**add_regular_token(char **result,
									int *result_count, char *token);
int								should_process_entry(struct dirent *entry,
									const char *pattern);
char							**handle_match_failure(char **matches,
									int count, DIR *dir);

// *************** SHELL FUNCTIONS ***************

/* shell/shell_init.c */
int								init_shell(t_shell *shell, char **envp);
void							cleanup_shell(t_shell *shell);

/* shell/shell_command.c */
int								handle_empty_command(t_shell *shell);
int								check_has_content(t_shell *shell);
void							process_regular_command(char *line,
									t_shell *shell);
int								process_line(char *line, t_shell *shell);

/* shell/shell_command_split.c */
char							**split_and_commands(char *line);

/* shell/shell_command_exec.c */
int								execute_single_command(char *command,
									t_shell *shell);
int								execute_and_commands(char **commands,
									t_shell *shell);
void							handle_and_commands(char *line, t_shell *shell);

/* shell/shell_loop.c */
int								main_loop(t_shell *shell);

/* shell/token_filter.c*/
int								is_inside_quotes(char *line, char *pos);

#endif
