/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 16:00:00 by vaires-m          #+#    #+#             */
/*   Updated: 2025/11/19 11:30:55 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_chars(char *cmd, char *replaced, char *temp)
{
	while (*cmd)
	{
		temp = handle_quotes_and_redir(replaced, &cmd);
		if (temp != replaced)
		{
			if (!temp)
				return (NULL);
			replaced = temp;
			continue ;
		}
		temp = handle_special_chars(replaced, &cmd);
		if (temp != replaced)
		{
			if (!temp)
				return (NULL);
			replaced = temp;
			continue ;
		}
		if (check_input(*cmd, &replaced) == -1)
			return (NULL);
		cmd++;
	}
	return (replaced);
}

char	*process_input_chars(char *cmd)
{
	char	*replaced;
	char	*temp;
	char	*parsed;

	replaced = NULL;
	temp = NULL;
	parsed = replace_chars(cmd, replaced, temp);
	if (!parsed)
		parsing_error(parsed);
	return (parsed);
}
