/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_filter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 10:20:00 by vabatist          #+#    #+#             */
/*   Updated: 2025/11/19 14:40:39 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_inside_quotes(char *line, char *pos)
{
	int		single_quote;
	int		double_quote;
	char	*p;

	single_quote = 0;
	double_quote = 0;
	p = line;
	while (p < pos)
	{
		if (*p == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (*p == '"' && !single_quote)
			double_quote = !double_quote;
		p++;
	}
	return (single_quote || double_quote);
}

/*
static int	count_tokens_arr(char **arr)
{
	int	n;

	n = 0;
	while (arr && arr[n])
		n++;
	return (n);
}

static int	has_quotes(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

static void	compact_tokens(char ***parr, int n)
{
	char	**old;
	char	**nv;
	int		i;
	int		k;

	old = *parr;
	nv = ft_calloc(sizeof(char *), n + 1);
	if (!nv)
		ft_free();
	i = 0;
	k = 0;
	while (i < n)
	{
		if (old[i][0] != '\0' || has_quotes(old[i]))
			nv[k++] = old[i];
		else
			free(old[i]);
		i++;
	}
	nv[k] = NULL;
	free(old);
	*parr = nv;
}
*/

void	remove_empty_unquoted_tokens(void)
{
	(void)get_shell();
	return ;
}
