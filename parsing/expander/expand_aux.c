/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 15:20:54 by vabatist          #+#    #+#             */
/*   Updated: 2025/10/28 18:23:17 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Retrieves the value of an environment variable.
 * This function searches the linked list of environment variables
 * for a variable matching the provided name and returns its value.
 * If the variable is not found, it returns NULL.
 * @param var The name of the environment variable to look up
 * @return A newly allocated string containing the variable's value,
 * or NULL if the variable is not found.
 * The caller is responsible for freeing the returned string.
 * @note If memory allocation fails, the function returns NULL.
 */
char	*ft_get_env(char *var)
{
	t_envc	*envc;
	char	*expanded;

	envc = get_shell()->env;
	expanded = NULL;
	while (envc)
	{
		if (!ft_strcmp(envc->var, var))
		{
			expanded = ft_strdup(envc->value);
			break ;
		}
		envc = envc->next;
	}
	return (expanded);
}

/**
 * @brief Checks if a string is enclosed in single quotes.
 * This function checks if the input string starts and ends with single quotes.
 * If both conditions are met, it returns 1 (true); otherwise, it returns
 * 0 (false).
 * @param str The input string to check
 * @return 1 if the string is enclosed in single quotes, 0 otherwise
 * @note The function assumes that the input string is not NULL
 * and has a length of at least 2.
 */
int	in_single_quotes(char *str)
{
	int	len;

	if (!str)
		return (0);
	len = ft_strlen(str);
	if (len < 2)
		return (0);
	if (str[0] == '\'' && str[len - 1] == '\'')
		return (1);
	return (0);
}

/**
 * @brief Trims leading and trailing whitespace from a string.
 * This function removes leading and trailing whitespace characters
 * from the input string and copies the trimmed result into the
 * provided final string buffer.
 * It handles cases where the string is enclosed in quotes.
 * @param result The input string to trim
 * @param final Pointer to the buffer where the trimmed string will be stored
 * @param i Pointer to an integer used for indexing during trimming
 * @return The pointer to the final trimmed string
 */
char	*trim_spaces(char *result, char **final, int *i)
{
	int	j;

	*i = 0;
	j = 0;
	while (result[*i])
	{
		(*final)[j++] = result[(*i)++];
	}
	(*final)[j] = 0;
	return (*final);
}

/**
 * @brief Converts the last command's exit status to a string.
 * This function retrieves the exit status of the last executed command
 * from the global shell structure, converts it to a string using ft_itoa,
 * and returns the resulting string.
 * The caller is responsible for freeing the returned string.
 * @return A newly allocated string containing the exit status,
 * or NULL on memory allocation failure.
 * The caller is responsible for freeing the returned string.
 * @note If memory allocation fails, the function returns NULL.
 */
char	*parse_status(void)
{
	char	*cmd_status;

	cmd_status = ft_itoa(get_shell()->command_status);
	if (!cmd_status)
		return (NULL);
	return (cmd_status);
}

void	expand_tokens(void)
{
	int			i;
	t_tokens	*tokens;
	char		*expanded;

	tokens = get_shell()->tokens;
	while (tokens)
	{
		i = -1;
		while (tokens->token && tokens->token[++i])
		{
			expanded = expand_token(tokens->token[i]);
			if (expanded == NULL)
				ft_free();
			free(tokens->token[i]);
			tokens->token[i] = expanded;
		}
		tokens = tokens->next;
	}
}
