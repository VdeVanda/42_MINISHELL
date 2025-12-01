/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes_escape.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:00:00 by vaires-m          #+#    #+#             */
/*   Updated: 2025/10/15 18:44:26 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*handle_unquoted_escape(char *token, int *i, char *result)
{
	if (token[*i + 1] == '$' || token[*i + 1] == '"' || token[*i + 1] == '\\'
		|| token[*i + 1] == '\'' || token[*i + 1] == ' ')
	{
		result = add_char_to_result(result, token[*i + 1]);
		if (!result)
			return (NULL);
		(*i)++;
	}
	else
	{
		result = add_char_to_result(result, token[*i]);
		if (!result)
			return (NULL);
	}
	return (result);
}

char	*handle_escape_sequences(char *token, int *i, char *result)
{
	if (token[*i + 1] == '$')
		result = handle_escaped_char(result, '$', i);
	else if (token[*i + 1] == '"')
		result = handle_escaped_char(result, '"', i);
	else if (token[*i + 1] == '\\')
		result = handle_escaped_char(result, '\\', i);
	else
	{
		result = add_char_to_result(result, token[*i]);
		if (!result)
			return (NULL);
	}
	return (result);
}

char	*handle_escaped_char(char *result, char c, int *i)
{
	result = add_char_to_result(result, c);
	if (!result)
		return (NULL);
	(*i)++;
	return (result);
}

char	*handle_variable_expansion(char *token, int *i, char *result)
{
	result = expand_at_position(token, i, result);
	if (!result)
		return (NULL);
	(*i)--;
	return (result);
}
