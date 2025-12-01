/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 15:48:40 by vabatist          #+#    #+#             */
/*   Updated: 2025/11/02 15:48:43 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*add_char_to_result(char *result, char c)
{
	char	*temp;
	char	*new_result;

	temp = ft_calloc(2, sizeof(char));
	if (!temp)
		return (free(result), NULL);
	temp[0] = c;
	new_result = ft_strjoin(result, temp);
	free(result);
	free(temp);
	return (new_result);
}

static char	*handle_status_variable(char *result, int *i)
{
	char	*var_value;
	char	*new_result;

	(*i)++;
	var_value = parse_status();
	if (!var_value)
		return (free(result), NULL);
	new_result = ft_strjoin(result, var_value);
	free(result);
	free(var_value);
	return (new_result);
}

char	*expand_at_position(char *token, int *i, char *result)
{
	char	*var_name;
	char	*var_value;
	char	*new_result;
	int		is_braced;

	(*i)++;
	if (token[*i] == '?')
		return (handle_status_variable(result, i));
	(*i)--;
	var_name = extract_variable_name(token, i, &is_braced);
	if (!var_name)
		return (free(result), NULL);
	var_value = ft_get_env(var_name);
	free(var_name);
	if (!var_value)
		var_value = ft_strdup("");
	if (!var_value)
		return (free(result), NULL);
	new_result = ft_strjoin(result, var_value);
	free(result);
	free(var_value);
	return (new_result);
}
