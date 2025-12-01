/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 19:45:00 by vaires-m          #+#    #+#             */
/*   Updated: 2025/10/31 00:32:11 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	fork_child_process(t_tokens *current, t_pipe_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		cleanup_child_inherited_memory();
		setup_pipe_io(data->prev_fd, data->pipe_fd, data->has_next);
		execute_child_command(current, data->envp);
	}
	else if (pid > 0)
	{
		current->pid = pid;
		return (pid);
	}
	else
	{
		perror("fork");
		return (-1);
	}
	return (0);
}

int	handle_child_process(t_tokens *current, int prev_fd, int *pipe_fd,
		char **envp)
{
	t_pipe_data	data;

	data.prev_fd = prev_fd;
	data.pipe_fd = pipe_fd;
	data.has_next = (current->next != NULL);
	data.envp = envp;
	return (fork_child_process(current, &data));
}

int	wait_for_children(t_tokens *tokens)
{
	t_tokens	*current;
	int			status;
	int			exit_status;

	exit_status = 0;
	current = tokens;
	handle_sig(PARENT_WAIT);
	while (current)
	{
		if (current->pid > 0)
		{
			waitpid(current->pid, &status, 0);
			if (WIFEXITED(status))
				exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				exit_status = 128 + WTERMSIG(status);
			current->pid = 0;
		}
		current = current->next;
	}
	handle_sig(PARENT);
	return (exit_status);
}

void	manage_pipe_fds(int *prev_fd, int *pipe_fd, int has_next)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (has_next)
	{
		close(pipe_fd[1]);
		*prev_fd = pipe_fd[0];
	}
	else
		*prev_fd = -1;
}

void	setup_pipe_io(int prev_fd, int *pipe_fd, int has_next)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (has_next)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
	}
}
