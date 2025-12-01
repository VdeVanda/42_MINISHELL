/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 22:53:54 by vabatist          #+#    #+#             */
/*   Updated: 2025/09/10 16:45:27 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Validates the replaced string pointer at the end of check_input().
 *
 * This function performs a basic null-check validation on the string being
 * built during parsing. It serves as a safety validator in the parsing pipeline.
 *
 * @param replaced The string being built during parsing
 * @return -1 if replaced is NULL (error condition), 0 if valid (success)
 */
int	check_input_aux(char *replaced)
{
	if (!replaced)
		return (-1);
	return (0);
}

static void	populate_lst2(t_tokens *tokens)
{
	int	type;
	int	i;
	int	j;

	i = 0;
	while (tokens->token[i])
	{
		type = get_type(tokens->token[i]);
		if (type)
		{
			populate_redir(&tokens->token[i], tokens, type);
			j = i + 1 + (tokens->token[i + 1] != NULL);
			while (tokens->token[j])
				tokens->token[i++] = tokens->token[j++];
			tokens->token[i] = NULL;
			i = 0;
		}
		else
			i++;
	}
}

void	populate_lst(char **arr_split)
{
	t_tokens	*lsttokens;

	lsttokens = ft_lsttoken(arr_split);
	if (!lsttokens)
	{
		ft_free_err(arr_split, "Error creating list.");
		exit(1);
	}
	if (!get_shell()->tokens)
		get_shell()->tokens = lsttokens;
	else
		ft_tokensadd_back(&get_shell()->tokens, lsttokens);
	populate_lst2(lsttokens);
	if (lsttokens->token[0])
		lsttokens->is_builtin = check_builtin(lsttokens->token[0]);
}

/**
 * @brief Core string building function that grows a string by one character.
 *
 * This function is used throughout the parser to build the encoded
 * command string, character by character, managing memory automatically.
 * It allocates new memory, copies the existing content,
 * appends the new character, and frees the old string.
 *
 * @param curr The current string (will be freed)
 * @param c The character to append
 * @return A new string with the character appended, or NULL on failure
 *
 * @warning The function frees the input string and returns a new one
 * @note Always use: str = add_char(str, 'c'); Never: add_char(str, 'c');
 */
char	*add_char(char *curr, char c)
{
	int		len;
	char	*ret;

	len = 0;
	if (curr && *curr)
		len = ft_strlen(curr);
	ret = ft_calloc(sizeof(char), len + 1 + 1);
	if (!ret)
		return (NULL);
	if (len > 0)
		ft_strlcpy(ret, curr, len + 1);
	free(curr);
	ret[len] = c;
	ret[len + 1] = '\0';
	return (ret);
}

/**
 * @brief Validates that all quotes in the command string are properly paired.
 *
 * This function takes the raw command string and checks if all quotes
 * (single and double) are properly paired. It is called BEFORE any other
 * parsing logic to ensure quote syntax is valid.
 *
 * @param cmd The raw command string to validate
 * @return 1 if quotes are properly closed, -1 if unclosed quotes found
 *
 * @note Prints error message to stderr if unclosed quotes are detected
 */
int	closed_quotes(char *cmd)
{
	int		i;
	char	q;

	i = 0;
	q = 0;
	while (cmd[i])
	{
		if (!q && (cmd[i] == '\'' || cmd[i] == '\"'))
			q = cmd[i];
		else if (cmd[i] == q)
			q = 0;
		i++;
	}
	if (q)
	{
		ft_putstr_fd("Unclosed quotes.\n", 2);
		return (-1);
	}
	return (1);
}
