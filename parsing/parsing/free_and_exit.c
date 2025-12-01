/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:29:04 by vabatist          #+#    #+#             */
/*   Updated: 2025/09/27 12:45:26 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Frees all allocated memory in the shell environment.
 *
 * This function is called when an error occurs during parsing or execution,
 * and it ensures that all resources are properly released
 * to prevent memory leaks.
 * Currently, most cleanup functions are commented out during development.
 *
 * @note This function will exit the program with status 1 after cleanup
 */
void	ft_free(void)
{
	free_lst();
	ft_putstr_fd("Error creating lists.\n", 2);
	exit(1);
}

/**
 * @brief Final free to list and array of strings inside list
 * @note This function iterates through the linked list of tokens,
 * freeing each node's associated resources including redirection lists
 * and token arrays, before freeing the node itself.
 */
void	free_lst(void)
{
	t_tokens	*temp;
	t_tokens	*temp2;

	temp = get_shell()->tokens;
	while (temp)
	{
		temp2 = temp->next;
		free_redir(&temp->redir);
		free_arr2(temp->token);
		free(temp);
		temp = temp2;
	}
	get_shell()->tokens = NULL;
}

/**
 * @brief Frees an array of strings and prints an error message.
 *
 * This function is used to handle errors during parsing or execution.
 * It frees the provided array of strings and prints the specified error message
 * to standard output. Additional cleanup functions are currently commented out
 * during development.
 *
 * @param arr The array of strings to free (can be NULL)
 * @param err The error message to print
 *
 * @note Most memory cleanup functions are disabled during development
 */
void	ft_free_err(char **arr, char *err)
{
	if (arr)
		printf("%s\n", err);
}

/**
 * @brief Frees the linked list of redirection nodes.
 *
 * This function iterates through the linked list of redirection nodes,
 * freeing each node's filename and the node itself. It ensures that
 * all resources associated with redirections are properly released.
 *
 * @param redir Pointer to the head of the redirection list to free
 */
void	free_redir(t_redir **redir)
{
	t_redir	*temp;

	if (!get_shell()->tokens || !*redir || !(*redir)->filename)
		return ;
	while (*redir)
	{
		temp = *redir;
		*redir = (*redir)->next;
		if (temp->filename)
		{
			free(temp->filename);
			temp->filename = NULL;
		}
		free(temp);
		temp = NULL;
	}
	*redir = NULL;
}

/**
 * @brief Handles parsing errors with cleanup and program termination.
 *
 * This function checks if a parsed string exists and frees it if necessary,
 * prints an error message, and exits the program with error status.
 * Additional cleanup functions are currently commented out during development.
 *
 * @param parsed The parsed string to free (can be NULL)
 *
 * @note This function will exit the program with status 1 after cleanup
 * @note Most memory cleanup functions are disabled during development
 */
void	parsing_error(char *parsed)
{
	if (parsed)
		free(parsed);
	printf("Error parsing command line.\n");
	ft_lstclear_env(&get_shell()->env);
	free_redir(&get_shell()->tokens->redir);
	rl_clear_history();
	exit(1);
}
