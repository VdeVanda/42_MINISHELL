/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_varname.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 23:35:00 by vabatist          #+#    #+#             */
/*   Updated: 2025/11/02 15:49:35 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	calculate_var_length(int i, int start, int is_braced)
{
	int	adjustment;

	adjustment = 0;
	if (is_braced)
		adjustment = 1;
	return (i - start - adjustment);
}

static void	init_brace_and_start(char *token, int *i, int *is_braced,
				int *start)
{
	(*i)++;
	*is_braced = 0;
	if (token[*i] == '{')
	{
		*is_braced = 1;
		(*i)++;
	}
	*start = *i;
}

static void	consume_var_body(char *token, int *i, int is_braced)
{
	if (!is_braced && ft_isdigit(token[*i]))
		(*i)++;
	else if (is_braced || ft_isalpha(token[*i]) || token[*i] == '_')
	{
		while (token[*i] && (ft_isalnum(token[*i]) || token[*i] == '_'))
			(*i)++;
	}
}

char	*extract_variable_name(char *token, int *i, int *is_braced)
{
	int		start;
	int		len;
	char	*var_name;

	init_brace_and_start(token, i, is_braced, &start);
	consume_var_body(token, i, *is_braced);
	if (*is_braced && token[*i] == '}')
		(*i)++;
	len = calculate_var_length(*i, start, *is_braced);
	var_name = ft_substr(token, start, len);
	return (var_name);
}
