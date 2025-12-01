/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:54:52 by vabatist          #+#    #+#             */
/*   Updated: 2025/09/10 16:56:31 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @file ft_lst.c
 * @brief Functions to manage the linked list of tokens.
 *
 * This file contains functions to manage the linked list of tokens
 * created during the parsing of shell commands.
 *
 * Functions included:
 * - ft_lsttoken(): Creates a new token node
 * - ft_tokenslast(): Returns the last node in the token list
 * - ft_tokensadd_front(): Adds a new node to the front of the token list
 * - ft_tokensadd_back(): Adds a new node to the back of the token list
 * - get_shell(): Returns a pointer to the global shell structure
 *
 * This module is essential for managing the parsed commands
 * and their associated data.
 */

/**
 * @brief Creates a new token node and initializes its fields.
 *
 * This function is used to build the linked list of tokens
 * that represent the parsed commands. It allocates memory for a new
 * token node and initializes all its fields to default values.
 *
 * @param args The array of strings representing the command and its arguments
 * @return A pointer to the newly created token node, or NULL on failure
 */
t_tokens	*ft_lsttoken(char **args)
{
	t_tokens	*lsttokens;

	lsttokens = ft_calloc(1, sizeof(t_tokens));
	if (!lsttokens)
		return (NULL);
	lsttokens->token = args;
	if (!lsttokens->token)
		return (NULL);
	lsttokens->type = 0;
	lsttokens->io.fd_in = 0;
	lsttokens->io.fd_out = 0;
	lsttokens->io.saved_stdin = -1;
	lsttokens->io.saved_stdout = -1;
	lsttokens->redir = NULL;
	lsttokens->next = NULL;
	return (lsttokens);
}

/**
 * @brief Returns the last node in the token list.
 *
 * This function is used to traverse the list and find the end,
 * which is useful for adding new nodes to the back of the list.
 *
 * @param tokens The head of the token list
 * @return A pointer to the last node in the token list, or NULL if list is empty
 */
t_tokens	*ft_tokenslast(t_tokens *tokens)
{
	if (tokens)
	{
		while (tokens->next != NULL)
			tokens = tokens->next;
	}
	return (tokens);
}

/**
 * @brief Adds a new node to the front of the token list.
 *
 * This function updates the head of the list to point to the new node.
 * It is used to prepend tokens to the list.
 *
 * @param tokens A pointer to the head of the token list
 * @param node The new node to add to the front of the list
 * @return void
 */
void	ft_tokensadd_front(t_tokens **tokens, t_tokens *node)
{
	node->next = *tokens;
	*tokens = node;
}

/**
 * @brief Adds a new node to the back of the token list.
 *
 * This function traverses the list to find the last node
 * and appends the new node.
 * If the list is empty, it sets the head to the new node.
 *
 * @param token A pointer to the head of the token list
 * @param node The new node to add to the back of the list
 * @return void
 */
void	ft_tokensadd_back(t_tokens **token, t_tokens *node)
{
	if (*token)
		ft_tokenslast(*token)->next = node;
	else
		*token = node;
}

/**
 * @brief Returns a pointer to the global shell structure.
 *
 * This function is used to access and modify the shell's state,
 * including tokens, environment variables, and command status.
 *
 * @return t_shell* A pointer to the global shell structure
 */
t_shell	*get_shell(void)
{
	static t_shell	shell;

	return (&shell);
}
