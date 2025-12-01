/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:00:00 by vaires-m          #+#    #+#             */
/*   Updated: 2025/11/19 11:40:54 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_has_content(t_shell *shell)
{
	t_tokens	*t;

	t = shell->tokens;
	while (t)
	{
		if ((t->token && t->token[0] && t->token[0][0] != '\0') || t->redir)
			return (1);
		t = t->next;
	}
	return (0);
}

int	handle_empty_command(t_shell *shell)
{
	ft_putstr_fd("minishell: command not found\n", STDERR_FILENO);
	shell->command_status = 127;
	free_tokens(shell->tokens);
	shell->tokens = NULL;
	return (1);
}

static int	has_unquoted_and_operator(char *line)
{
	int		single_quote;
	int		double_quote;
	char	*p;

	single_quote = 0;
	double_quote = 0;
	p = line;
	while (*p)
	{
		if (*p == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (*p == '"' && !single_quote)
			double_quote = !double_quote;
		else if (*p == '&' && *(p + 1) == '&'
			&& !single_quote && !double_quote)
			return (1);
		p++;
	}
	return (0);
}

void	process_regular_command(char *line, t_shell *shell)
{
	if (has_unquoted_and_operator(line))
	{
		handle_and_commands(line, shell);
		return ;
	}
	execute_single_command(line, shell);
}

int	process_line(char *line, t_shell *shell)
{
	process_regular_command(line, shell);
	return (0);
}
