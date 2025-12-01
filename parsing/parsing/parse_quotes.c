/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:51:01 by vabatist          #+#    #+#             */
/*   Updated: 2025/11/19 11:30:46 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Processes quotes in the command string.
 *
 * This function handles both single quotes (') and double quotes (")
 * by extracting the content within the quotes and returning it as a new string.
 * It uses a flag variable to match the opening and closing quote types.
 *
 * @param replaced Pointer to the string being built (can be NULL initially)
 * @param cmd Pointer to the command string being processed (will be advanced)
 *
 * @return A new string with the quoted content included,
 * or NULL on memory allocation failure
 *
 * @note The function advances the cmd pointer past the processed quote section
 */
static char	*handle_quote_found(char *replaced, char *temp)
{
	char	*joined;

	if (replaced)
	{
		joined = ft_strjoin(replaced, temp);
		free(temp);
		free(replaced);
		return (joined);
	}
	else
		return (temp);
}

char	*parse_quotes(char *replaced, char **cmd)
{
	int		len;
	char	flag;
	char	*temp;

	temp = *cmd;
	flag = *temp;
	len = 1;
	while (temp[len] && temp[len] != flag && len < 1000)
		len++;
	if (temp[len] != flag || len >= 1000)
	{
		if (replaced)
			free(replaced);
		return (NULL);
	}
	temp = ft_substr(temp, 0, len + 1);
	*cmd += len + 1;
	if (!temp)
		return (NULL);
	return (handle_quote_found(replaced, temp));
}
