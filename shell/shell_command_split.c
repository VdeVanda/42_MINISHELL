/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_command_split.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 00:45:00 by vaires-m          #+#    #+#             */
/*   Updated: 2025/11/19 11:45:31 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_and_operators(char *line)
{
	char	*pos;
	int		count;
	size_t	len;

	count = 1;
	pos = line;
	len = ft_strlen(line);
	while (1)
	{
		pos = ft_strnstr(pos, "&&", len - (pos - line));
		if (!pos)
			break ;
		if (!is_inside_quotes(line, pos))
			count++;
		pos += 2;
	}
	return (count);
}

static void	process_and_split(char **result, char *line, char **start, int *i)
{
	char	*pos;
	char	*trimmed;

	pos = ft_strnstr(*start, "&&", ft_strlen(line) - (*start - line));
	if (!pos || is_inside_quotes(line, pos))
		return ;
	result[*i] = ft_substr(*start, 0, pos - *start);
	if (result[*i])
	{
		trimmed = ft_strtrim(result[*i], " \t");
		free(result[*i]);
		result[*i] = trimmed;
	}
	*start = pos + 2;
	(*i)++;
}

static char	**fill_result_array(char **result, char *line, char *start, int i)
{
	char	*pos;
	size_t	len;

	len = ft_strlen(line);
	while (1)
	{
		pos = ft_strnstr(start, "&&", len - (start - line));
		if (!pos)
			break ;
		if (is_inside_quotes(line, pos))
		{
			pos += 2;
			continue ;
		}
		process_and_split(result, line, &start, &i);
	}
	result[i] = ft_strtrim(start, " \t");
	result[i + 1] = NULL;
	return (result);
}

static char	**allocate_and_split(char *line, int count)
{
	char	**result;
	char	*start;
	int		i;

	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	start = line;
	i = 0;
	return (fill_result_array(result, line, start, i));
}

char	**split_and_commands(char *line)
{
	int	count;

	count = count_and_operators(line);
	return (allocate_and_split(line, count));
}
