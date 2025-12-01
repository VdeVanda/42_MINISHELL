/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 16:00:00 by vaires-m          #+#    #+#             */
/*   Updated: 2025/10/03 13:03:30 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	contains_pipe(t_tokens *token)
{
	int	token_count;

	token_count = 0;
	while (token)
	{
		token_count++;
		token = token->next;
	}
	return (token_count > 1);
}

int	handle_pipe(t_tokens *tokens, char **envp)
{
	t_tokens	*current;
	int			pipe_fd[2];
	int			prev_fd;
	int			has_next;

	if (!tokens || !tokens->next)
		return (execute_command(tokens, envp));
	current = tokens;
	prev_fd = -1;
	while (current)
	{
		has_next = (current->next != NULL);
		if (has_next && pipe(pipe_fd) == -1)
		{
			perror("pipe");
			return (1);
		}
		if (handle_child_process(current, prev_fd, pipe_fd, envp) == -1)
			return (1);
		manage_pipe_fds(&prev_fd, pipe_fd, has_next);
		current = current->next;
	}
	if (prev_fd != -1)
		close(prev_fd);
	return (wait_for_children(tokens));
}
