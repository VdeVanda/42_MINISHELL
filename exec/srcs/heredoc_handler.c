/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 16:00:00 by vaires-m          #+#    #+#             */
/*   Updated: 2025/10/15 18:49:35 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*read_heredoc_input(char *delimiter, int quoted_delimiter)
{
	char	*content;

	content = ft_strdup("");
	if (!content)
		return (NULL);
	g_signal_status = 0;
	handle_sig(HEREDOC);
	rl_event_hook = check_signal_during_readline;
	content = handle_heredoc_loop(content, delimiter, quoted_delimiter);
	rl_event_hook = NULL;
	handle_sig(PARENT);
	return (content);
}

int	process_heredoc(char *delimiter, int pipe_fd[2], int quoted_delimiter)
{
	char	*content;
	int		result;

	if (!delimiter)
		return (-1);
	content = read_heredoc_input(delimiter, quoted_delimiter);
	if (!content && g_signal_status != SIGINT)
		content = ft_strdup("");
	if (g_signal_status == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (-1);
	}
	result = write_heredoc_to_pipe(content, pipe_fd);
	free(content);
	return (result);
}
