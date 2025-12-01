/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_expansion_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 16:00:00 by vaires-m          #+#    #+#             */
/*   Updated: 2025/10/01 09:56:22 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_expanded_array(char **expanded)
{
	int	j;

	j = 0;
	while (expanded[j])
		free(expanded[j++]);
	free(expanded);
}

char	**add_expanded_matches(char **result, int *result_count,
			char **expanded)
{
	int	j;

	j = 0;
	while (expanded[j])
	{
		result = realloc(result, sizeof(char *) * (*result_count + 2));
		result[*result_count] = ft_strdup(expanded[j]);
		(*result_count)++;
		j++;
	}
	return (result);
}

char	**add_regular_token(char **result, int *result_count, char *token)
{
	char	*new_token;

	new_token = ft_strdup(token);
	if (!new_token)
		return (result);
	result = realloc(result, sizeof(char *) * (*result_count + 2));
	if (!result)
	{
		free(new_token);
		return (NULL);
	}
	result[*result_count] = new_token;
	(*result_count)++;
	result[*result_count] = NULL;
	return (result);
}
