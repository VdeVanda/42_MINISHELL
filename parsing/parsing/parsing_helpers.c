/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 16:00:00 by vaires-m          #+#    #+#             */
/*   Updated: 2025/11/19 11:29:57 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_quotes_and_redir(char *replaced, char **cmd)
{
	char	*temp;

	if (**cmd == '\'' || **cmd == '\"')
	{
		temp = parse_quotes(replaced, cmd);
		if (temp == NULL)
			return (NULL);
		return (temp);
	}
	else if (**cmd == '<' || **cmd == '>')
	{
		temp = parse_redir(replaced, cmd);
		if (temp == NULL)
			return (free(replaced), NULL);
		return (temp);
	}
	return (replaced);
}

char	*handle_special_chars(char *replaced, char **cmd)
{
	char	*temp;

	if (**cmd == '&' && *(*cmd + 1) == '&')
	{
		temp = add_char(replaced, '\4');
		if (!temp)
			return (free(replaced), NULL);
		*cmd += 2;
		return (temp);
	}
	return (replaced);
}

int	check_input(char c, char **replaced)
{
	char	*temp;

	temp = NULL;
	if (is_whitespace(c))
	{
		temp = add_char(*replaced, '\2');
		if (!temp)
			return (-1);
		*replaced = temp;
	}
	else if (c == '|')
	{
		temp = add_char(*replaced, '\3');
		if (!temp)
			return (-1);
		*replaced = temp;
	}
	else
	{
		temp = add_char(*replaced, c);
		if (!temp)
			return (-1);
		*replaced = temp;
	}
	return (check_input_aux(*replaced));
}
