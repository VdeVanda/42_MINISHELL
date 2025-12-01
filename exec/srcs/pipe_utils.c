/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 19:45:00 by vaires-m          #+#    #+#             */
/*   Updated: 2025/11/01 18:57:42 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	cleanup_and_execute_builtin(char **expanded_tokens, char **envp,
				int should_free)
{
	int	builtin_status;

	builtin_status = 0;
	execute_builtin(expanded_tokens, envp, &builtin_status);
	if (should_free)
		free_split(expanded_tokens);
	exit(builtin_status);
}

static void	exec_with_cmd_path(char *cmd_path, char **expanded_tokens,
	int should_free)
{
	execve(cmd_path, expanded_tokens, get_shell()->env_arr);
	perror("execve");
	free(cmd_path);
	if (should_free)
		free_split(expanded_tokens);
	exit(126);
}

static void	handle_command_not_found(char **expanded_tokens, int should_free)
{
	if (ft_strchr(expanded_tokens[0], '/')
		&& access(expanded_tokens[0], F_OK) == 0)
	{
		if (should_free)
			free_split(expanded_tokens);
		exit(126);
	}
	ft_putstr_fd(expanded_tokens[0], STDERR_FILENO);
	if (ft_strchr(expanded_tokens[0], '/'))
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	else
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	if (should_free)
		free_split(expanded_tokens);
	exit(127);
}

static void	cleanup_and_execute_external(char **expanded_tokens,
	int should_free)
{
	char	*cmd_path;

	cmd_path = get_command_path(expanded_tokens[0]);
	if (cmd_path)
		exec_with_cmd_path(cmd_path, expanded_tokens, should_free);
	handle_command_not_found(expanded_tokens, should_free);
}

void	execute_child_command(t_tokens *current, char **envp)
{
	char	**expanded_tokens;
	int		should_free;

	handle_sig(CHILD);
	if (current->redir)
		setup_redirections(current->redir);
	expanded_tokens = expand_globs(current->token);
	should_free = 0;
	if (!expanded_tokens)
		expanded_tokens = current->token;
	else
		should_free = 1;
	if (is_builtin(expanded_tokens[0]))
	{
		cleanup_and_execute_builtin(expanded_tokens, envp, should_free);
	}
	else
	{
		cleanup_and_execute_external(expanded_tokens, should_free);
	}
	exit(127);
}
