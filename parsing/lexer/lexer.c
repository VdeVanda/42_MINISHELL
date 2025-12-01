/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 22:53:01 by vabatist          #+#    #+#             */
/*   Updated: 2025/10/29 11:47:20 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if a single character is a shell operator.
 *
 * This function determines if a character needs special handling during parsing.
 *
 * Special Characters Detected:
 * - | (pipe) - Connects commands (e.g., ls | grep txt)
 * - < (input redirection) - Redirects input from file (e.g., cat < file.txt)
 * - > (output redirection) - Redirects output to file
 * (e.g., echo hello > file.txt)
 *
 * @param c The character to check
 * @return 1 if the character is a special operator, 0 otherwise
 */
int	is_special_char(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

/**
 * @brief Checks if a command line contains any meaningful text content.
 *
 * This function iterates through the command line, skipping whitespace and
 * special characters, and returns true if it finds any alphanumeric characters
 * or underscores.
 *
 * @param cmd_line The command line to check
 * @return true if the command line has meaningful text, false otherwise
 */
bool	has_text(char *cmd_line)
{
	int	i;

	i = 0;
	while (cmd_line[i])
	{
		if (!is_whitespace(cmd_line[i]) && !is_special_char(cmd_line[i]))
			break ;
		i++;
	}
	if (!cmd_line[i])
		return (false);
	return (true);
}

/**
 * @brief Validates that pipe characters are not at the beginning of a command.
 *
 * This function checks the first non-whitespace char to ensure proper syntax:
 * - If it finds an alphanumeric char OR a special char that's NOT a pipe
 *   (<, >), it returns true (valid syntax)
 * - If it finds a pipe (|) as the first meaningful character, it prints an error
 *   and returns false
 *
 * @param cmd The command string to validate
 * @param len The length of the command string
 * @return true if pipe syntax is valid, false otherwise
 */
static bool	check_pipe(char *cmd, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		while (is_whitespace(cmd[i]) && i < len)
			i++;
		if (ft_isalnum(cmd[i]) || (is_special_char(cmd[i]) && cmd[i] != '|'))
			return (true);
		else if (cmd[i] == '|')
		{
			ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 2);
			get_shell()->command_status = 2;
			return (false);
		}
		i++;
	}
	return (true);
}

/**
 * @brief Validates that && operators are not isolated or improperly placed.
 *
 * This function checks for common && syntax errors:
 * - Standalone && (just "&&" with no commands)
 * - && at the beginning of input
 * - && at the end of input without continuation
 *
 * @param cmd The command string to validate
 * @return true if && syntax is valid, false otherwise
 */
static bool	check_and_operator(char *cmd)
{
	char	*trimmed;
	bool	result;

	trimmed = ft_strtrim(cmd, " \t\n");
	if (!trimmed)
		return (true);
	if (ft_strcmp(trimmed, "&&") == 0)
	{
		ft_putstr_fd("bash: syntax error near unexpected token `&&'\n", 2);
		get_shell()->command_status = 2;
		result = false;
	}
	else if (ft_strncmp(trimmed, "&&", 2) == 0 && trimmed[2] == '\0')
	{
		ft_putstr_fd("bash: syntax error near unexpected token `&&'\n", 2);
		get_shell()->command_status = 2;
		result = false;
	}
	else
		result = true;
	free(trimmed);
	return (result);
}

/**
 * @brief Main syntax validator that orchestrates all syntax checks.
 *
 * This function performs validation in a specific order before parsing begins:
 *
 * Step 1: Check quotes (FIRST and most critical):
 * - Validates that all quotes (' and ") are properly paired
 * - If quotes are unclosed, immediately fails - no further checks
 *
 * Step 2: Check && operator syntax:
 * - Validates that && operators aren't isolated or improperly placed
 * - Prevents buffer overflow issues during command splitting
 *
 * Step 3: Validate command structure:
 * - Checks overall command syntax (redirections, operators, etc.)
 * - Sets error status to 2 if validation fails
 *
 * Step 4: Check pipe syntax (FINAL check):
 * - Ensures pipes aren't at the beginning of commands
 * - Returns the final validation result
 *
 * @param cmd The command string to validate
 * @return true if syntax is valid, false otherwise
 */
bool	check_syntax(char *cmd)
{
	int		len;
	bool	char_found;
	bool	quotes;

	char_found = false;
	quotes = false;
	len = ft_strlen(cmd);
	if (closed_quotes(cmd) == -1)
		return (false);
	if (!check_and_operator(cmd))
		return (false);
	if (!validate_cmd(cmd, len, char_found, quotes))
	{
		get_shell()->command_status = 2;
		return (false);
	}
	return (check_pipe(cmd, len));
}
