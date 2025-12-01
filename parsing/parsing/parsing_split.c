/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 18:35:00 by vaires-m          #+#    #+#             */
/*   Updated: 2025/11/19 14:34:48 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_string_tokens(char *str)
{
	int	in_single_quotes;
	int	in_double_quotes;
	int	i;
	int	count;

	in_single_quotes = 0;
	in_double_quotes = 0;
	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		else if (str[i] == '"' && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		else if (str[i] == '\2' && !in_single_quotes && !in_double_quotes)
			count++;
		i++;
	}
	return (count);
}

static void	process_char_for_token(char *str, int *vars, char **result)
{
	int	*in_single_quotes;
	int	*in_double_quotes;
	int	*start;
	int	*i;
	int	*count;

	in_single_quotes = &vars[0];
	in_double_quotes = &vars[1];
	start = &vars[2];
	i = &vars[3];
	count = &vars[4];
	if (str[*i] == '\'' && !*in_double_quotes)
		*in_single_quotes = !*in_single_quotes;
	else if (str[*i] == '"' && !*in_single_quotes)
		*in_double_quotes = !*in_double_quotes;
	else if (str[*i] == '\2' && !*in_single_quotes && !*in_double_quotes)
	{
		if (*i > *start)
			result[(*count)++] = ft_substr(str, *start, *i - *start);
		*start = *i + 1;
	}
}

static void	create_tokens(char *str, char **result)
{
	int	vars[5];

	vars[0] = 0;
	vars[1] = 0;
	vars[2] = 0;
	vars[3] = 0;
	vars[4] = 0;
	while (str[vars[3]])
	{
		process_char_for_token(str, vars, result);
		vars[3]++;
	}
	if (vars[3] > vars[2])
		result[vars[4]++] = ft_substr(str, vars[2], vars[3] - vars[2]);
}

char	**smart_split_spaces(char *str)
{
	char	**result;
	int		count;

	count = count_string_tokens(str);
	result = ft_calloc(sizeof(char *), count + 2);
	if (!result)
		return (NULL);
	create_tokens(str, result);
	return (result);
}

void	split_spaces(void)
{
	static int	i;
	char		**arr_split;

	arr_split = NULL;
	arr_split = smart_split_spaces(get_shell()->arr_2d[i]);
	if (!arr_split)
	{
		parsing_error(NULL);
	}
	populate_lst(arr_split);
	if (get_shell()->arr_2d[++i])
		split_spaces();
	i = 0;
}
