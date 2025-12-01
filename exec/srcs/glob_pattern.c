/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_pattern.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 16:00:00 by vaires-m          #+#    #+#             */
/*   Updated: 2025/09/26 19:28:30 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	match_asterisk(const char *pattern, const char *string)
{
	while (*pattern == '*')
		pattern++;
	if (*pattern == '\0')
		return (1);
	while (*string != '\0')
	{
		if (match_pattern(pattern, string))
			return (1);
		string++;
	}
	return (match_pattern(pattern, string));
}

int	match_pattern(const char *pattern, const char *string)
{
	if (*pattern == '\0' && *string == '\0')
		return (1);
	if (*pattern == '*')
		return (match_asterisk(pattern, string));
	if (*pattern == '\0' || *string == '\0')
		return (0);
	if (*pattern == '?' || *pattern == *string)
		return (match_pattern(pattern + 1, string + 1));
	return (0);
}

int	has_wildcards(const char *str)
{
	return (ft_strchr(str, '*') != NULL || ft_strchr(str, '?') != NULL);
}
