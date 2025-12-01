/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes_aux.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 18:45:00 by vaires-m          #+#    #+#             */
/*   Updated: 2025/11/19 11:40:54 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*handle_quote_chars(char *token, int *i, int *quotes, char *result)
{
	if (token[*i] == '\'' && !quotes[1])
	{
		quotes[0] = !quotes[0];
		return (result);
	}
	else if (token[*i] == '"' && !quotes[0])
	{
		quotes[1] = !quotes[1];
		return (result);
	}
	result = add_char_to_result(result, token[*i]);
	if (!result)
		return (NULL);
	return (result);
}

char	*handle_escape_logic(char *token, int *i, char *result, int *quotes)
{
	if (token[*i] == '\\' && quotes[1])
	{
		result = handle_escape_sequences(token, i, result);
		if (!result)
			return (NULL);
	}
	else if (token[*i] == '\\' && !quotes[0] && !quotes[1] && token[*i + 1])
	{
		result = handle_unquoted_escape(token, i, result);
		if (!result)
			return (NULL);
	}
	return (result);
}

static int	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_' || c == '{' || c == '?');
}

char	*handle_variable_logic(char *token, int *i, char *result, int *quotes)
{
	if (token[*i] == '$' && token[*i + 1] && !quotes[0]
		&& is_valid_var_char(token[*i + 1]))
	{
		result = handle_variable_expansion(token, i, result);
		if (!result)
			return (NULL);
		return (result);
	}
	return (NULL);
}
