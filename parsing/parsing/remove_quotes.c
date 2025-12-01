/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 17:15:38 by vabatist          #+#    #+#             */
/*   Updated: 2025/11/12 12:50:26 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//static void	process_token_array(char **token_array)
//{
//	int		i;
//	char	*new;
//
//	i = -1;
//	while (token_array && token_array[++i])
//	{
//		new = ft_strdup_q(token_array[i]);
//		if (!new)
//			ft_free();
//		token_array[i] = new;
//	}
//}

static void	process_token_quotes(t_tokens *tokens)
{
	check_quotes_redir(tokens);
}

void	check_quotes_tokens(void)
{
	t_tokens	*tokens;

	tokens = get_shell()->tokens;
	while (tokens)
	{
		process_token_quotes(tokens);
		tokens = tokens->next;
	}
}

void	check_quotes_redir(t_tokens *tokens)
{
	t_redir	*redir;
	char	*new;

	redir = tokens->redir;
	while (redir)
	{
		new = ft_strdup_q(redir->filename);
		if (!new)
			ft_free();
		redir->filename = new;
		redir = redir->next;
	}
}
