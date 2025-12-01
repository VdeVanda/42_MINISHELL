/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 14:28:15 by vabatist          #+#    #+#             */
/*   Updated: 2025/11/19 14:40:39 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @file check_list.c
 * @brief Functions to check and clean up the token list after parsing.
 *
 * This file contains functions that ensure empty tokens are removed and the list
 * is properly formatted.
 * It is called at the end of the parsing process to ensure
 * that the token list is ready for execution.
 *
 * Functions included:
 * - count_idx(): Counts the number of non-empty tokens in a 2D array
 * - remove_empty_idx(): Removes empty tokens from a 2D array
 * - check_list(): Iterates through the token list and removes empty tokens
 *
 * This module is essential for maintaining the integrity of the token list
 * and ensuring that the shell can execute commands correctly.
 */

/**
 * @brief Counts the number of non-empty tokens in a 2D array.
 *
 * This function iterates through the command string to count the number
 * of non-empty tokens. It is used to determine how many valid tokens are
 * present in the command line after parsing, which helps in allocating
 * memory for the new array.
 *
 * @param tokens The 2D array of tokens to check
 * @return The count of non-empty tokens
 */
/**
 * @brief Checks if a token is an empty string enclosed in quotes.
 * 
 * This function determines if a token represents an empty quoted string
 * like "" or ''. These should be preserved as valid arguments.
 *
 * @param token The token string to check
 * @return 1 if token is empty quotes, 0 otherwise
 */
static int	is_empty_quotes(char *token)
{
	if (!token)
		return (0);
	if ((token[0] == '"' && token[1] == '"' && token[2] == '\0'))
		return (1);
	if ((token[0] == '\'' && token[1] == '\'' && token[2] == '\0'))
		return (1);
	return (0);
}

/**
 * @brief Counts the number of non-empty tokens in a 2D array.
 *
 * This function iterates through the command string to count the number
 * of non-empty tokens. Empty quoted strings ("" or '') are counted as valid.
 *
 * @param tokens The 2D array of tokens to check
 * @return The count of non-empty tokens
 */
static int	count_idx(char **tokens)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tokens[i])
	{
		if (tokens[i][0] || is_empty_quotes(tokens[i]))
			j++;
		i++;
	}
	return (j);
}

/**
 * @brief Removes empty tokens from a 2D array of strings.
 *
 * This function iterates through the array, checking each token,
 * and creates a new array that only contains non-empty tokens.
 * Empty quoted strings ("" or '') are preserved as they are valid arguments.
 *
 * @param tokens The original 2D array of tokens
 * @return A new 2D array with empty unquoted tokens removed
 */
static char	**remove_empty_idx(char **tokens)
{
	int		i;
	int		j;
	char	**new;
	int		count;

	i = -1;
	j = 0;
	count = count_idx(tokens);
	new = ft_calloc(sizeof(char *), count + 1);
	if (!new)
		ft_free();
	while (tokens[++i])
	{
		if (!tokens[i][0] && !is_empty_quotes(tokens[i]))
		{
			free(tokens[i]);
			continue ;
		}
		else
			new[j++] = tokens[i];
	}
	free(tokens);
	new[j] = 0;
	return (new);
}

/**
 * @brief Iterates through the token list to check for and remove empty tokens.
 *
 * This function ensures that the token list is clean and ready for execution.
 * It is called at the end of the parsing process to ensure that the token list
 * is properly formatted.
 * The function processes each token node in the linked list
 * and removes any empty token strings within each node's token array.
 * 
 * Note: Empty strings from quoted arguments (e.g., "" or '') are preserved
 * as they are valid arguments in bash.
 */
void	check_list(void)
{
	int			i;
	t_tokens	*tokens;

	tokens = get_shell()->tokens;
	while (tokens)
	{
		i = 0;
		while (tokens->token && tokens->token[i])
		{
			if (!tokens->token[i][0] && !is_empty_quotes(tokens->token[i]))
			{
				tokens->token = remove_empty_idx(tokens->token);
				continue ;
			}
			i++;
		}
		tokens = tokens->next;
	}
}
