/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 19:30:00 by vaires-m          #+#    #+#             */
/*   Updated: 2025/10/09 13:04:35 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setup_io_redirections(t_tokens *token)
{
	token->io.saved_stdin = dup(STDIN_FILENO);
	if (token->io.saved_stdin == -1)
	{
		perror("dup");
		return (1);
	}
	token->io.saved_stdout = dup(STDOUT_FILENO);
	if (token->io.saved_stdout == -1)
	{
		perror("dup");
		close(token->io.saved_stdin);
		token->io.saved_stdin = -1;
		return (1);
	}
	if (setup_redirections(token->redir) != 0)
	{
		restore_io(&token->io);
		return (1);
	}
	return (0);
}

static int	exec_command_with_execve(char *cmd_path, char **expanded_tokens,
					char **my_envp)
{
	handle_sig(CHILD);
	if (execve(cmd_path, expanded_tokens, my_envp) == -1)
	{
		perror("execve");
		exit(126);
	}
	return (0);
}

static int	handle_parent_process(pid_t pid)
{
	int	status;
	int	exit_status;

	handle_sig(PARENT_WAIT);
	waitpid(pid, &status, 0);
	handle_sig(PARENT);
	if (WIFEXITED(status))
		exit_status = WEXITSTATUS(status);
	else
		exit_status = 1;
	return (exit_status);
}

int	fork_and_execute(char *cmd_path, char **expanded_tokens, char **my_envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		exec_command_with_execve(cmd_path, expanded_tokens, my_envp);
	else if (pid > 0)
		return (handle_parent_process(pid));
	else
	{
		perror("fork");
		return (1);
	}
	return (0);
}

char	*build_path(char *dir, char *cmd)
{
	char	*temp;
	char	*full_path;

	if (!dir || !cmd)
		return (NULL);
	temp = ft_strjoin(dir, "/");
	if (!temp)
		return (NULL);
	full_path = ft_strjoin(temp, cmd);
	free(temp);
	return (full_path);
}
