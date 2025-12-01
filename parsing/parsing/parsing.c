/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:25:23 by vabatist          #+#    #+#             */
/*   Updated: 2025/10/07 22:30:47 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @file parsing.c
 * @brief Main parsing logic for the minishell project.
 *
 * This file contains the main parsing logic for the minishell project.
 * It handles input parsing, command line processing, and syntax checking.
 * The parsing is done in a way that allows for flexible command structures
 * and proper handling of quotes and special characters.
 */

/**
 * @brief Recursively splits command segments by whitespace.
 * This function processes each command segment in the 2D array,
 * splitting them by whitespace (encoded
 * as '\2') and populating the token list.
 * @note This function uses recursion to process each segment.
 * @note It relies on the global shell
 * structure to access the command segments.
 */
static char	**split_2d_arr(char *parsed)
{
	char	**arr_2d;
	char	*and_ptr;

	and_ptr = ft_strchr(parsed, '\4');
	if (and_ptr)
	{
		arr_2d = ft_split(parsed, '\4');
		if (!arr_2d)
			return (NULL);
		get_shell()->has_and_operator = 1;
	}
	else
	{
		arr_2d = ft_split(parsed, '\3');
		if (!arr_2d)
			return (NULL);
		get_shell()->has_and_operator = 0;
	}
	return (arr_2d);
}

/**
 * @brief Processes individual characters and encodes them in the output string.
 *
 * This function is the character encoder in the parsing pipeline. It decides
 * how to encode each character based on its type:
 * - Whitespace characters: encoded as '\2' for later splitting
 * - Pipe characters ('|'): encoded as '\3' for command separation
 * - Other characters: preserved as-is
 *
 * @param c The current character being processed
 * @param replaced Pointer to the output string being built
 * @return 0 on success, -1 on memory allocation failure
 */
static void	process_command_splitting(char *parsed)
{
	char	**arr_2d;

	arr_2d = split_2d_arr(parsed);
	if (!arr_2d)
		parsing_error(parsed);
	free(parsed);
	get_shell()->arr_2d = arr_2d;
}

void	parse_input(char *cmd)
{
	char	*parsed;
	int		len;

	len = ft_strlen(cmd);
	if (len == 0)
		return ;
	parsed = process_input_chars(cmd);
	process_command_splitting(parsed);
	split_spaces();
	check_list();
}
