/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 16:26:26 by vabatist          #+#    #+#             */
/*   Updated: 2025/10/14 13:43:22 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Creates and initializes a new redirection node.
 *
 * @param arr Array containing the filename at index 1
 * @param lsttokens The token to handle error cleanup
 * @return A new redirection node, or NULL on failure (exits program)
 */
static t_redir	*create_redir_node(char **arr, t_tokens *lsttokens)
{
	t_redir	*curr;

	curr = lst_redir();
	if (!curr)
	{
		ft_free_err(arr, "Error creating redir node.");
		if (lsttokens->redir)
			free_redir(&lsttokens->redir);
		free_lst();
		exit(1);
	}
	return (curr);
}

/**
 * @brief Checks if a heredoc delimiter is quoted and removes quotes.
 *
 * @param delimiter The delimiter string (potentially quoted)
 * @return 1 if delimiter was quoted, 0 if not
 */
static int	process_heredoc_delimiter(char **delimiter)
{
	int		len;
	int		quoted;
	char	*new_delimiter;

	len = ft_strlen(*delimiter);
	quoted = 0;
	if (len >= 2 && (((*delimiter)[0] == '\'' && (*delimiter)[len - 1] == '\'')
		|| ((*delimiter)[0] == '"' && (*delimiter)[len - 1] == '"')))
	{
		quoted = 1;
		new_delimiter = ft_strdup_q(*delimiter);
		if (!new_delimiter)
			ft_free();
		*delimiter = new_delimiter;
	}
	return (quoted);
}

/**
 * @brief Handles heredoc processing for a redirection node.
 *
 * @param curr The redirection node
 * @param lsttokens The token containing heredoc file descriptor
 * @return 0 on success, -1 on failure
 */
static int	handle_heredoc_processing(t_redir *curr, t_tokens *lsttokens)
{
	int	quoted_delimiter;

	quoted_delimiter = process_heredoc_delimiter(&curr->filename);
	if (process_heredoc(curr->filename, lsttokens->heredoc_fd,
			quoted_delimiter) == -1)
	{
		free(curr->filename);
		free(curr);
		return (-1);
	}
	return (0);
}

/**
 * @brief Populates a redirection node and adds it
 * to the token's redirection list.
 *
 * This function creates a new redirection node, sets its filename and type,
 * and appends it to the linked list of redirections in the provided token.
 * It handles memory allocation failures by freeing resources and exiting.
 *
 * @param arr Array containing the filename at index 1
 * @param lsttokens The token to which the redirection will be added
 * @param type The type of redirection (e.g., REDIR_IN, REDIR_OUT)
 *
 * @note On memory allocation failure, frees resources and exits the program
 */
void	populate_redir(char **arr, t_tokens *lsttokens, int type)
{
	t_redir	*curr;

	curr = create_redir_node(arr, lsttokens);
	curr->filename = arr[1];
	free(arr[0]);
	arr[0] = NULL;
	curr->type = type;
	if (type == HERE_DOC)
	{
		if (handle_heredoc_processing(curr, lsttokens) == -1)
			return ;
	}
	if (!lsttokens->redir)
		lsttokens->redir = curr;
	else
		ft_lstadd_back_redir(&lsttokens->redir, curr);
}

/**
 * @brief Processes redirection operators in the command string.
 *
 * This function identifies redirection operators and encodes
 * them in the output string
 * with special markers for easier parsing later.
 * The function uses special markers (`\2`)
 * to denote the start and end of redirection operators,
 * creating a format like `\2>\2`.
 *
 * @param replaced The output string being built (can be NULL initially)
 * @param cmd Pointer to the command string being processed (will be advanced)
 * @return A new string with the redirection operators encoded,
 * or NULL on failure
 *
 * @note The function advances the cmd pointer past the processed
 * redirection operator
 * @note Memory management: frees intermediate strings and handles
 * replaced string joining
 */
char	*parse_redir(char *replaced, char **cmd)
{
	int		i;
	char	*redir;
	char	*temp;

	i = get_redir_len(*cmd);
	redir = ft_substr(*cmd, 0, i);
	if (!redir)
		return (NULL);
	temp = ft_strjoin("\2", redir);
	*cmd += i;
	free(redir);
	if (!temp)
		return (NULL);
	redir = ft_strjoin(temp, "\2");
	free(temp);
	if (!redir)
		return (NULL);
	if (replaced)
	{
		temp = ft_strjoin(replaced, redir);
		free(replaced);
		free(redir);
		return (temp);
	}
	return (redir);
}
