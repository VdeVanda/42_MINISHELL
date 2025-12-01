/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:00:00 by vaires-m          #+#    #+#             */
/*   Updated: 2025/11/19 11:59:16 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	handle_empty_line(char *line)
{
	if (!*line)
	{
		free(line);
		return (1);
	}
	return (0);
}

/* Process a single input line: add history, validate syntax, execute. */
static int	process_read_line(char *line, t_shell *shell)
{
	if (handle_empty_line(line))
		return (0);
	if (ft_strlen(line) > 0)
		add_history(line);
	if (!check_syntax(line))
	{
		free(line);
		return (0);
	}
	if (process_line(line, shell) == 1)
	{
		free(line);
		return (1);
	}
	free(line);
	return (0);
}

int	main_loop(t_shell *shell)
{
	char	*line;

	while (1)
	{
		if (g_signal_status == SIGINT)
			g_signal_status = 0;
		if (g_signal_status == EXIT_NORMAL || g_signal_status == EXIT_WITH_CODE)
			break ;
		line = readline("minishell$ ");
		if (!line)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			break ;
		}
		if (process_read_line(line, shell))
			break ;
	}
	cleanup_shell(shell);
	if (g_signal_status == EXIT_WITH_CODE)
		exit((unsigned char)shell->command_status);
	if (g_signal_status == EXIT_NORMAL)
		exit(0);
	exit((unsigned char)shell->command_status);
}
