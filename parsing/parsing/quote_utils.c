/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 21:58:00 by vaires-m          #+#    #+#             */
/*   Updated: 2025/11/12 12:28:34 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_escape_sequence(char *token, int *i, char *new, int *j)
{
	(*i)++;
	if (token[*i] == '\'' || token[*i] == '\"')
		new[(*j)++] = token[(*i)++];
	else
	{
		new[(*j)++] = '\\';
		new[(*j)++] = token[(*i)++];
	}
}

void	process_quote_char(char *token, int *i, char *q)
{
	if ((token[*i] == '\'' || token[*i] == '\"') && !*q)
		*q = token[(*i)++];
	else if (token[*i] == *q && *q != 0)
	{
		*q = 0;
		(*i)++;
	}
	else
		(*i)++;
}

static char	*process_token_chars(char *token, char *new)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	quote = 0;
	while (token[i])
	{
		if (!quote && (token[i] == '\'' || token[i] == '\"'))
		{
			quote = token[i];
			i++;
		}
		else if (quote && token[i] == quote)
		{
			quote = 0;
			i++;
		}
		else
			new[j++] = token[i++];
	}
	new[j] = '\0';
	return (new);
}

char	*ft_strdup_q(char *token)
{
	char	*new;

	if (!token)
		return (NULL);
	new = ft_calloc(sizeof(char), ft_strlen(token) + 1);
	if (!new)
		return (NULL);
	process_token_chars(token, new);
	free(token);
	return (new);
}
