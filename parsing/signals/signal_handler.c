/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 10:55:06 by vabatist          #+#    #+#             */
/*   Updated: 2025/10/14 17:17:06 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Signals in normal mode
 * @brief Handles SIGINT (Ctrl+C) signal in the main shell process.
 * This function is called when the user sends an interrupt signal
 * to the shell (e.g., by pressing Ctrl+C).
 * It writes a newline to the standard output,
 * moves the cursor to a new line in the readline interface,
 * clears the current input line, and redisplays the prompt.
 * @param signal The signal number (unused)
 */
static void	handle_sigint(int signal)
{
	(void)signal;
	g_signal_status = SIGINT;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/**
 * signals in heredoc mode
 * @brief Handles SIGINT (Ctrl+C) signal during heredoc input.
 * This function is called when the user sends an interrupt signal
 * while the shell is reading a heredoc (e.g., by pressing Ctrl+C).
 * It sets a global signal status variable to indicate that an interrupt
 * has occurred, allowing the heredoc reading process to handle the interruption
 * appropriately.
 * @param signal The signal number (unused)
 */
static void	handle_sigint_heredoc(int signal)
{
	(void)signal;
	g_signal_status = SIGINT;
}

/**
 * signals in parent process waiting for child to finish
 * @brief Handles SIGINT (Ctrl+C) signal in the parent process
 * while waiting for a child process to complete.
 * This function is called when the user sends an interrupt signal
 * to the shell while it is waiting for a child process
 * (e.g., during command execution that takes time).
 * It writes a newline to the standard output to indicate the interrupt.
 * @param signal The signal number (unused)
 */
static void	handle_sigint_parent(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n", 1);
}

/**
 * @brief Configures signal handling based on the specified mode.
 * This function sets up signal handlers for SIGINT and SIGQUIT
 * based on the provided mode, allowing different behaviors
 * in various contexts (e.g., parent process, child process, heredoc input).
 * @param mode The signal handling mode (PARENT, CHILD, HEREDOC, PARENT_WAIT)
 * @see t_sigs enum for mode definitions
 * @note The specific signal handling behavior for each mode
 * is defined in the respective handler functions.
 */
void	handle_sig(t_sigs mode)
{
	if (mode == PARENT)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (mode == HEREDOC)
	{
		signal(SIGINT, handle_sigint_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == PARENT_WAIT)
	{
		signal(SIGINT, handle_sigint_parent);
		signal(SIGQUIT, SIG_IGN);
	}
}
