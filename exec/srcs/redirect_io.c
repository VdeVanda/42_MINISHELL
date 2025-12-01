/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_io.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 20:20:00 by vaires-m          #+#    #+#             */
/*   Updated: 2025/09/26 20:28:41 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	restore_io(t_io *io)
{
	if (io->saved_stdin != -1)
	{
		if (dup2(io->saved_stdin, STDIN_FILENO) == -1)
		{
			perror("dup2 restore stdin");
			close(io->saved_stdin);
			io->saved_stdin = -1;
			return (1);
		}
		close(io->saved_stdin);
		io->saved_stdin = -1;
	}
	if (io->saved_stdout != -1)
	{
		if (dup2(io->saved_stdout, STDOUT_FILENO) == -1)
		{
			perror("dup2 restore stdout");
			close(io->saved_stdout);
			io->saved_stdout = -1;
			return (1);
		}
		close(io->saved_stdout);
		io->saved_stdout = -1;
	}
	return (0);
}

int	setup_io_backup(t_io *io)
{
	io->saved_stdin = dup(STDIN_FILENO);
	if (io->saved_stdin == -1)
	{
		perror("dup");
		return (1);
	}
	io->saved_stdout = dup(STDOUT_FILENO);
	if (io->saved_stdout == -1)
	{
		perror("dup");
		close(io->saved_stdin);
		io->saved_stdin = -1;
		return (1);
	}
	return (0);
}
