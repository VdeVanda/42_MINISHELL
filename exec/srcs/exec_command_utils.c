/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 20:40:00 by vaires-m          #+#    #+#             */
/*   Updated: 2025/10/31 00:20:59 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**prepare_expanded_tokens(t_tokens *token)
{
	char	**expanded_tokens;

	expanded_tokens = expand_globs(token->token);
	if (!expanded_tokens)
		expanded_tokens = token->token;
	return (expanded_tokens);
}

int	handle_redirection_setup(t_tokens *token, char **expanded_tokens)
{
	if (token->redir && setup_io_redirections(token) != 0)
	{
		if (expanded_tokens && expanded_tokens != token->token)
			free_split(expanded_tokens);
		return (1);
	}
	return (0);
}

void	cleanup_execution(t_tokens *token, char **expanded_tokens)
{
	if (token->redir)
		restore_io(&token->io);
	if (expanded_tokens && expanded_tokens != token->token)
		free_split(expanded_tokens);
}

int	execute_builtin_command(char **expanded_tokens, char **my_envp)
{
	int	exit_status;

	exit_status = 0;
	execute_builtin(expanded_tokens, my_envp, &exit_status);
	return (exit_status);
}

int	execute_external_command(char **expanded_tokens, char **my_envp)
{
	char	*cmd_path;
	int		exit_status;

	cmd_path = get_command_path(expanded_tokens[0]);
	if (!cmd_path)
	{
		if (ft_strchr(expanded_tokens[0], '/')
			&& access(expanded_tokens[0], F_OK) == 0)
			return (126);
		ft_putstr_fd(expanded_tokens[0], STDERR_FILENO);
		if (ft_strchr(expanded_tokens[0], '/'))
			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		else
			ft_putstr_fd(": command not found\n", STDERR_FILENO);
		return (127);
	}
	exit_status = fork_and_execute(cmd_path, expanded_tokens, my_envp);
	free(cmd_path);
	return (exit_status);
}
