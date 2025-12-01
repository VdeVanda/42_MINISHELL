/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 16:00:00 by vaires-m          #+#    #+#             */
/*   Updated: 2025/09/26 20:22:26 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_redirection_type(t_redir *current)
{
	if (current->type == REDIR_IN)
		return (handle_input_redirect(current->filename));
	else if (current->type == REDIR_OUT)
		return (handle_output_redirect(current->filename));
	else if (current->type == REDIR_OUT_FORCE)
		return (handle_output_redirect(current->filename));
	else if (current->type == REDIR_OUT_APPND)
		return (handle_append_redirect(current->filename));
	else if (current->type == HERE_DOC)
		return (handle_heredoc_redirect());
	return (0);
}

int	setup_redirections(t_redir *redir)
{
	t_redir	*current;

	current = redir;
	while (current)
	{
		if (process_redirection_type(current) != 0)
			return (1);
		current = current->next;
	}
	return (0);
}

int	handle_redirect(t_tokens *token, char **my_envp)
{
	int	exit_status;

	if (setup_io_backup(&token->io) != 0)
		return (1);
	if (setup_redirections(token->redir) != 0)
	{
		restore_io(&token->io);
		return (1);
	}
	exit_status = execute_command(token, my_envp);
	restore_io(&token->io);
	return (exit_status);
}
