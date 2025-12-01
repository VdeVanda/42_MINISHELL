/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 22:00:00 by vaires-m          #+#    #+#             */
/*   Updated: 2025/11/02 15:49:14 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_token_with_quotes(char *token, char *result)
{
	int		i;
	int		quotes[2];

	i = 0;
	quotes[0] = 0;
	quotes[1] = 0;
	while (token[i])
	{
		result = process_char_in_token(token, &i, result, quotes);
		if (!result)
			return (NULL);
		i++;
	}
	return (result);
}

static char	*handle_escape_char(char *token, int *i, char *result, int *quotes)
{
	char	*temp_result;

	temp_result = handle_escape_logic(token, i, result, quotes);
	if (temp_result)
		result = temp_result;
	return (result);
}

static char	*handle_dollar_char(char *token, int *i, char *result, int *quotes)
{
	char	*temp_result;

	temp_result = handle_variable_logic(token, i, result, quotes);
	if (temp_result)
		result = temp_result;
	else
	{
		result = add_char_to_result(result, token[*i]);
		if (!result)
			return (NULL);
	}
	return (result);
}

char	*process_char_in_token(char *token, int *i, char *result, int *quotes)
{
	if (quotes[0] && token[*i] != '\'')
	{
		result = add_char_to_result(result, token[*i]);
		if (!result)
			return (NULL);
		return (result);
	}
	if (token[*i] == '\'' || token[*i] == '"')
	{
		result = handle_quote_chars(token, i, quotes, result);
		if (!result)
			return (NULL);
	}
	else if (token[*i] == '\\')
		result = handle_escape_char(token, i, result, quotes);
	else if (token[*i] == '$')
		result = handle_dollar_char(token, i, result, quotes);
	else
	{
		result = add_char_to_result(result, token[*i]);
		if (!result)
			return (NULL);
	}
	return (result);
}
