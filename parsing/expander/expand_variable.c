/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 15:20:30 by vabatist          #+#    #+#             */
/*   Updated: 2025/11/02 15:49:26 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	should_skip_expansion(char *token);

char	*expand_token(char *token)
{
	char	*result;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	if (should_skip_expansion(token))
	{
		free(result);
		return (ft_strdup(token));
	}
	return (expand_token_with_quotes(token, result));
}

static int	should_skip_expansion(char *token)
{
	if (!token || !*token)
		return (0);
	if (token[0] == '\'' && token[ft_strlen(token) - 1] != '\'')
		return (1);
	if (token[0] != '\'' && token[ft_strlen(token) - 1] == '\'')
		return (1);
	return (0);
}
