/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_expansion_core.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 16:00:00 by vaires-m          #+#    #+#             */
/*   Updated: 2025/10/01 09:55:32 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**process_token(char **result, int *result_count, char *token)
{
	char	**expanded;

	if (has_wildcards(token))
	{
		expanded = expand_wildcard(token);
		if (expanded)
		{
			result = add_expanded_matches(result, result_count, expanded);
			free_expanded_array(expanded);
		}
		else
		{
			result = add_regular_token(result, result_count, token);
		}
	}
	else
		result = add_regular_token(result, result_count, token);
	return (result);
}

char	**expand_globs(char **tokens)
{
	char	**result;
	int		result_count;
	int		i;

	if (!tokens)
		return (NULL);
	result = NULL;
	result_count = 0;
	i = 0;
	while (tokens[i])
	{
		result = process_token(result, &result_count, tokens[i]);
		if (!result)
		{
			return (NULL);
		}
		i++;
	}
	if (result)
		result[result_count] = NULL;
	return (result);
}
