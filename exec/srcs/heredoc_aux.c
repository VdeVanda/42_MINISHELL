/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_aux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 16:00:00 by vaires-m          #+#    #+#             */
/*   Updated: 2025/10/15 18:54:47 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*process_heredoc_line(char *content, char *line, int expand_vars)
{
	char	*temp;
	char	*expanded_line;

	if (expand_vars)
	{
		expanded_line = expand_token(line);
		if (!expanded_line)
			expanded_line = ft_strdup("");
	}
	else
		expanded_line = ft_strdup(line);
	temp = ft_strjoin(content, expanded_line);
	free(expanded_line);
	if (!temp)
		return (NULL);
	free(content);
	content = temp;
	temp = ft_strjoin(content, "\n");
	free(content);
	if (!temp)
		return (NULL);
	return (temp);
}

int	should_continue_heredoc(char *line, char *delimiter)
{
	if (ft_strcmp(line, delimiter) == 0)
	{
		free(line);
		return (0);
	}
	return (1);
}

int	check_signal_during_readline(void)
{
	if (g_signal_status == SIGINT)
	{
		rl_done = 1;
		return (1);
	}
	return (0);
}

char	*handle_heredoc_loop(char *content, char *delimiter,
	int quoted_delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || g_signal_status == SIGINT)
		{
			free(content);
			rl_event_hook = NULL;
			handle_sig(PARENT);
			return (NULL);
		}
		if (!should_continue_heredoc(line, delimiter))
			break ;
		content = process_heredoc_line(content, line, !quoted_delimiter);
		free(line);
		if (!content)
		{
			rl_event_hook = NULL;
			return (NULL);
		}
	}
	return (content);
}

int	write_heredoc_to_pipe(char *content, int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	if (content)
	{
		write(pipe_fd[1], content, ft_strlen(content));
	}
	close(pipe_fd[1]);
	return (0);
}
