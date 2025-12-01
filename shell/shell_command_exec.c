/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_command_exec.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 00:45:00 by vaires-m          #+#    #+#             */
/*   Updated: 2025/11/19 10:47:46 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	execute_parsed_command(t_shell *shell)
{
	expand_tokens();
	if (!check_has_content(shell))
	{
		remove_empty_unquoted_tokens();
		if (shell->tokens && handle_empty_command(shell))
			return ;
	}
	remove_empty_unquoted_tokens();
	check_quotes_tokens();
	process_commands(shell->tokens, shell->env_arr);
	free_tokens(shell->tokens);
	shell->tokens = NULL;
}

static void	cleanup_shell_state(t_shell *shell)
{
	if (shell->arr_2d)
	{
		free_arr2(shell->arr_2d);
		shell->arr_2d = NULL;
	}
}

int	execute_single_command(char *command, t_shell *shell)
{
	g_signal_status = 0;
	parse_input(command);
	if (shell->tokens)
		execute_parsed_command(shell);
	cleanup_shell_state(shell);
	return (shell->command_status);
}

int	execute_and_commands(char **commands, t_shell *shell)
{
	int	i;
	int	exit_status;

	i = 0;
	exit_status = 0;
	while (commands[i])
	{
		exit_status = execute_single_command(commands[i], shell);
		if (exit_status != 0)
			break ;
		i++;
	}
	return (exit_status);
}

void	handle_and_commands(char *line, t_shell *shell)
{
	char	**and_commands;

	and_commands = split_and_commands(line);
	if (and_commands)
	{
		execute_and_commands(and_commands, shell);
		free_split(and_commands);
	}
}
