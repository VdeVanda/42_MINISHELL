/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 16:00:00 by vaires-m          #+#    #+#             */
/*   Updated: 2025/10/01 12:45:26 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

int	should_process_entry(struct dirent *entry, const char *pattern)
{
	return (entry->d_name[0] != '.' || pattern[0] == '.');
}

char	**handle_match_failure(char **matches, int count, DIR *dir)
{
	cleanup_matches(matches, count);
	closedir(dir);
	return (NULL);
}
