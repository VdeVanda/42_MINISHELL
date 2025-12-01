/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 22:51:38 by vabatist          #+#    #+#             */
/*   Updated: 2025/10/18 23:56:41 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Skips whitespace characters in the command line.
 *
 * @param cmd The command string to process
 * @param i Pointer to the current index in the command string
 */
static void	skip_spaces(char *cmd, int *i)
{
	while (is_whitespace(cmd[*i]))
		(*i)++;
}

/**
 * @brief Looks for alphanumeric characters or underscores in the command line.
 *
 * If it finds any valid characters, it sets the char_found flag to true.
 *
 * @param c The character to validate
 * @param char_found Pointer to the flag indicating if valid chars were found
 */
static void	validate_alnum(char c, bool *char_found)
{
	if (ft_isalnum(c) || c == '_')
		*char_found = true;
}

/**
 * @brief Prints an error message for unexpected tokens in the command line.
 *
 * If a special character is found at the start of the command line,
 * it prints an error message indicating a syntax error.
 *
 * @param c The unexpected character that caused the error
 * @return false Always returns false to indicate an error
 */
static bool	print_err(char c)
{
	printf("bash: syntax error near unexpected token `%c'\n", c);
	return (false);
}

/**
 * @brief Validates the command line for syntax errors.
 *
 * This function performs comprehensive syntax validation by checking:
 * 1. If the command line starts with a pipe character (|), it returns false
 * 2. It skips whitespace and checks for alphanumeric characters or underscores
 * 3. If it encounters a special character (|, <, >) without preceding text,
 *    it prints an error and returns false
 * 4. It handles quotes, toggling the quotes flag when encountering a quote char
 * 5. It ensures that special characters are not followed by whitespace
 *    or another special character
 * 6. It properly handles double operators like ">>" and "<<"
 *
 * @param cmd_line The command line string to validate
 * @param len The length of the command line
 * @param char_found Flag indicating if valid characters have been found
 * @param quotes Flag indicating if we are currently inside quotes
 * @return true if the command line is valid, false otherwise
 */
bool	validate_cmd(char *cmd_line, int len, bool char_found, bool quotes)
{
	int		i;

	i = -1;
	while (i < len && cmd_line[++i])
	{
		skip_spaces(cmd_line, &i);
		validate_alnum(cmd_line[i], &char_found);
		if (is_special_char(cmd_line[i]) && !char_found && !quotes
			&& (!has_text(&cmd_line[i + 1]) || !cmd_line[i + 1]))
			return (print_err(cmd_line[i]));
		else if (is_special_char(cmd_line[i]) && !has_text(&cmd_line[i])
			&& !quotes)
			return (print_err(cmd_line[i]));
		else if (is_special_char(cmd_line[i]) && char_found == true)
		{
			char_found = false;
			if (!ft_strncmp(&cmd_line[i], ">>", 2) || !ft_strncmp(&cmd_line[i],
					"<<", 2))
				continue ;
		}
		else if (cmd_line[i] == '\"' || cmd_line[i] == '\'')
			quotes = !quotes;
	}
	return (true);
}
