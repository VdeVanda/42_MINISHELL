/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 23:56:57 by vaires-m          #+#    #+#             */
/*   Updated: 2025/11/19 11:59:16 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_command_type(char **expanded_tokens, char **my_envp,
				t_tokens *token);

char	*get_command_path(char *cmd)
{
	char	**path_dirs;

	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (check_absolute_path(cmd));
	path_dirs = get_path_dirs();
	return (search_in_path_dirs(path_dirs, cmd));
}

int	execute_command(t_tokens *token, char **my_envp)
{
	char	**expanded_tokens;
	int		exit_status;

	exit_status = 0;
	if (!token || !token->token || !token->token[0])
		return (1);
	expanded_tokens = prepare_expanded_tokens(token);
	if (handle_redirection_setup(token, expanded_tokens) != 0)
		return (1);
	exit_status = execute_command_type(expanded_tokens, my_envp, token);
	cleanup_execution(token, expanded_tokens);
	return (exit_status);
}

static int	execute_command_type(char **expanded_tokens, char **my_envp,
								t_tokens *token)
{
	(void)token;
	if (is_builtin(expanded_tokens[0]))
		return (execute_builtin_command(expanded_tokens, my_envp));
	else
		return (execute_external_command(expanded_tokens, my_envp));
}

void	process_commands(t_tokens *tokens, char **my_envp)
{
	int	exit_status;

	if (!tokens)
		return ;
	if (contains_pipe(tokens))
		exit_status = handle_pipe(tokens, my_envp);
	else
		exit_status = execute_command(tokens, my_envp);
	if (g_signal_status != EXIT_WITH_CODE && g_signal_status != EXIT_NORMAL)
		get_shell()->command_status = exit_status;
}

char	**execute_builtin(char **av, char **my_envp, int *status)
{
	if (!av || !av[0])
	{
		*status = 1;
		return (my_envp);
	}
	return (dispatch_builtin(av, my_envp, status));
}
