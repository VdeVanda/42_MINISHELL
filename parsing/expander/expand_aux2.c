/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_aux2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 15:21:02 by vabatist          #+#    #+#             */
/*   Updated: 2025/10/26 13:58:38 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if a string contains only whitespace
 * or is enclosed in double quotes.
 * This function iterates through the input string to determine
 * if it consists solely of whitespace characters or if it is
 * enclosed within double quotes.
 * If the string contains any non-whitespace characters outside of quotes,
 * the function returns 0.
 * If the string is entirely whitespace or properly quoted, it returns 1.
 * @param exp The input string to check
 * @return 1 if the string is only whitespace or quoted, 0 otherwise
 * @note The function assumes that quotes are properly closed.
 */
static int	check_quotes(char *exp)
{
	int	i;

	i = 0;
	while (exp[i])
	{
		if (exp[i] == '"' || exp[i] == '\'')
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Checks if a string is empty or contains only whitespace.
 * This function iterates through the input string to determine if it is NULL,
 * empty, or consists solely of whitespace characters. It also checks if the
 * string is properly quoted.
 * @param exp The input string to check
 * @return 0 if the string is NULL, empty, or contains only whitespace;
 * otherwise returns the count of whitespace characters
 */
int	check_ws(char *exp)
{
	int	i;
	int	j;

	if (!exp)
		return (0);
	if (check_quotes(exp) == 0)
		return (0);
	i = 0;
	j = 0;
	while (exp[i])
	{
		if (is_whitespace(exp[i]))
			j++;
		i++;
	}
	return (j);
}

/**
 * @brief Helper function to recreate the token array after expansion.
 * This function constructs a new token array by replacing the token
 * at index `i` with the expanded string `exp`, which may contain
 * multiple tokens separated by spaces. It allocates memory
 * for the new array and copies over the existing tokens,
 * inserting the expanded tokens in place of the original.
 * @param new The new token array being constructed
 * @param exp The expanded string to insert
 * @param tok The original token array
 * @param i The index of the token to replace
 * @return The newly constructed token array,
 * or NULL on memory allocation failure
 * @note The function assumes that `exp` is a valid string
 * and `tok` is a NULL-terminated array.
 * @note The caller is responsible for freeing the returned array.
 */
static char	**recreate_tokens2(char **new, char *exp, char **tok, int i)
{
	char	**exp_arr;
	int		j;
	int		k;

	exp_arr = ft_split(exp, ' ');
	free(exp);
	if (!exp_arr)
		return (NULL);
	j = 0;
	k = i;
	while (exp_arr[j])
		new[k++] = exp_arr[j++];
	while (tok[++i])
		new[k++] = tok[i];
	new[k] = NULL;
	free(tok);
	if (exp_arr)
		free(exp_arr);
	return (new);
}

/**
 * @brief Recreates the token array after expanding a variable.
 * This function constructs a new token array by replacing the token
 * at index `i` with the expanded string `exp`, which may contain
 * multiple tokens separated by spaces. It allocates memory
 * for the new array and copies over the existing tokens,
 * inserting the expanded tokens in place of the original.
 * It also frees the old token array and any temporary arrays used.
 * @param i The index of the token to replace
 * @param count The current count of tokens
 * @param tok The original token array
 * @param exp The expanded string to insert
 * @return The newly constructed token array,
 * or NULL on memory allocation failure
 * @note The function assumes that `exp` is a valid string and `tok` is
 * a NULL-terminated array.
 * @note The caller is responsible for freeing the returned array.
 */
char	**recreate_tokens(int i, int count, char **tok, char *exp)
{
	char	**new_tokens;
	char	**result;
	int		j;
	int		k;

	j = count_tokens(tok);
	count += 1 + j;
	new_tokens = ft_calloc(sizeof(char *), count);
	if (!new_tokens)
		ft_free();
	k = -1;
	while (++k < i)
		new_tokens[k] = tok[k];
	result = recreate_tokens2(new_tokens, exp, tok, i);
	if (!result)
	{
		free(new_tokens);
		ft_free();
	}
	return (result);
}

/**
 * @brief Checks if a character is a special shell character.
 * This function determines if the given character is one of the
 * special chars used in shell syntax,
 * such as '/', '.', ',', ':', '\"', or '\''.
 * These characters often have special meanings in shell commands and scripts.
 * @param c The character to check
 * @return 1 if the character is a special shell character, 0 otherwise
 * @note This function is used to identify characters that may affect
 * tokenization or parsing in shell commands.
 */
int	special_char(char c)
{
	if (c == '/' || c == '.' || c == ',' || c == ':' || c == '\"' || c == '\'')
		return (1);
	return (0);
}
