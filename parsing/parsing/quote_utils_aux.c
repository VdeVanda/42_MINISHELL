/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils_aux.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 18:30:00 by vaires-m          #+#    #+#             */
/*   Updated: 2025/10/15 18:30:00 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*copy_between_quotes(char *token, char *new, int len)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (i < len - 1)
	{
		new[j++] = token[i++];
	}
	new[j] = '\0';
	return (new);
}

char	*copy_entire_token(char *token, char *new, int len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < len)
	{
		new[j++] = token[i++];
	}
	new[j] = '\0';
	return (new);
}
