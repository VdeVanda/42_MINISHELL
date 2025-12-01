/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 00:47:52 by vabatist          #+#    #+#             */
/*   Updated: 2025/09/10 16:42:10 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if a character is a whitespace character.
 *
 * This function identifies whitespace characters including space (ASCII 32)
 * and control characters from 9-13 (tab, newline, vertical tab,
 * form feed, carriage return).
 *
 * @param c The character to check
 * @return 1 if the character is whitespace, 0 otherwise
 */
int	is_whitespace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

/**
 * @brief Counts the number of tokens in a 2D array of strings.
 *
 * This function iterates through a NULL-terminated array of strings
 * and returns the total count of elements.
 *
 * @param arr_split The 2D array of strings to count
 * @return The number of tokens in the array, or 0 if the array is empty
 */
int	count_tokens(char **arr_split)
{
	int	i;

	i = 0;
	if (!arr_split[i])
		return (0);
	while (arr_split[i])
		i++;
	return (i);
}

/**
 * @brief Checks if a token is a built-in shell command.
 *
 * This function compares the input token against known built-in commands
 * and returns a unique integer code for each built-in command.
 *
 * Built-in commands and their codes:
 * - echo: 1
 * - cd: 2
 * - pwd: 3
 * - export: 4
 * - unset: 5
 * - exit: 6
 * - env: 7
 *
 * @note Requires ft_strcmp to be implemented in libft
 *
 * @param token The command token to check
 * @return Integer code for the built-in command, or 0 if not a built-in
 */
int	check_builtin(char *token)
{
	if (!ft_strcmp(token, "echo"))
		return (1);
	if (!ft_strcmp(token, "cd"))
		return (2);
	if (!ft_strcmp(token, "pwd"))
		return (3);
	if (!ft_strcmp(token, "export"))
		return (4);
	if (!ft_strcmp(token, "unset"))
		return (5);
	if (!ft_strcmp(token, "exit"))
		return (6);
	if (!ft_strcmp(token, "env"))
		return (7);
	return (0);
}
