/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 18:45:00 by vaires-m          #+#    #+#             */
/*   Updated: 2025/10/09 21:15:52 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Determines the length of a redirection operator in the command string.
 *
 * This function checks for and identifies the following redirection operators:
 * - `>` (output redirection) - length 1
 * - `>>` (append output redirection) - length 2
 * - `<` (input redirection) - length 1
 * - `<<` (here-document) - length 2
 *
 * @param tok The command string to check
 * @return The length of the redirection operator (1 or 2), or 0 if none found
 *
 * @note Used to correctly parse and handle redirection operators
 * in shell commands
 */
int	get_redir_len(char *tok)
{
	if (tok[0] == '<' || tok[0] == '>')
	{
		if (tok[0] == '>' && tok[1] == '>')
			return (2);
		else if (tok[0] == '>' && tok[1] == '|')
			return (2);
		else if (tok[0] == '<' && tok[1] == '<')
			return (2);
		else if (tok[0] == '>')
			return (1);
		else if (tok[0] == '<')
			return (1);
		return (0);
	}
	return (0);
}

/**
 * @brief Determines the type of redirection based on the token string.
 *
 * This function maps redirection operator strings to their corresponding
 * enumeration values defined in `t_type`. It recognizes the following operators:
 * - `<`  : REDIR_IN
 * - `>`  : REDIR_OUT
 * - `>|` : REDIR_OUT_FORCE
 * - `>>` : REDIR_OUT_APPND
 * - `<<` : HERE_DOC
 *
 * @param tok The token string representing the redirection operator
 * @return The corresponding t_type value, or SIMPLE (0) if not a redirection
 *
 * @note Used during parsing to classify tokens for execution handling
 */
int	get_type(char *tok)
{
	if (tok[0] == '<' || tok[0] == '>')
	{
		if (!ft_strcmp(tok, "<<"))
			return (5);
		else if (!ft_strcmp(tok, ">>"))
			return (4);
		else if (!ft_strcmp(tok, ">|"))
			return (9);
		else if (!ft_strcmp(tok, ">"))
			return (3);
		else if (!ft_strcmp(tok, "<"))
			return (2);
	}
	return (0);
}
