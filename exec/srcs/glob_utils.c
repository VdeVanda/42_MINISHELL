/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 16:00:00 by vaires-m          #+#    #+#             */
/*   Updated: 2025/09/26 19:28:31 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_matches(char **matches, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(matches[i]);
		i++;
	}
	free(matches);
}

char	**resize_matches_array(char **matches, int *capacity)
{
	char	**new_matches;

	if (*capacity == 0)
		*capacity = 8;
	else
		*capacity = *capacity * 2;
	new_matches = realloc(matches, sizeof(char *) * (*capacity + 1));
	return (new_matches);
}

int	add_match_to_array(char ***matches, int *count, int *capacity,
		const char *name)
{
	char	**new_matches;

	if (*count >= *capacity)
	{
		new_matches = resize_matches_array(*matches, capacity);
		if (!new_matches)
			return (0);
		*matches = new_matches;
	}
	(*matches)[*count] = ft_strdup(name);
	if (!(*matches)[*count])
		return (0);
	(*count)++;
	return (1);
}

char	**handle_no_matches(const char *pattern)
{
	char	**matches;

	matches = malloc(sizeof(char *) * 2);
	if (!matches)
		return (NULL);
	matches[0] = ft_strdup(pattern);
	if (!matches[0])
	{
		free(matches);
		return (NULL);
	}
	matches[1] = NULL;
	return (matches);
}
