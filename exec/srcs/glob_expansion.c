/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 16:00:00 by vaires-m          #+#    #+#             */
/*   Updated: 2025/10/01 12:45:10 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

static char	**finalize_matches(char **matches, int count, const char *pattern)
{
	if (count == 0)
		return (handle_no_matches(pattern));
	matches[count] = NULL;
	return (matches);
}

static int	init_wildcard_search(DIR **dir)
{
	*dir = opendir(".");
	if (!*dir)
		return (0);
	return (1);
}

static int	process_directory_entries(DIR *dir, const char *pattern,
				t_match_data *data)
{
	struct dirent	*entry;

	entry = readdir(dir);
	while (entry)
	{
		if (should_process_entry(entry, pattern))
		{
			if (match_pattern(pattern, entry->d_name))
			{
				if (!add_match_to_array(&data->matches, &data->count,
						&data->capacity, entry->d_name))
					return (0);
			}
		}
		entry = readdir(dir);
	}
	return (1);
}

char	**expand_wildcard(const char *pattern)
{
	DIR				*dir;
	t_match_data	data;

	if (!init_wildcard_search(&dir))
		return (NULL);
	data.matches = NULL;
	data.count = 0;
	data.capacity = 0;
	if (!process_directory_entries(dir, pattern, &data))
		return (handle_match_failure(data.matches, data.count, dir));
	closedir(dir);
	return (finalize_matches(data.matches, data.count, pattern));
}
