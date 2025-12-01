/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 16:00:00 by vaires-m          #+#    #+#             */
/*   Updated: 2025/09/26 19:28:25 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token_array(char **token)
{
	int	i;

	if (!token)
		return ;
	i = 0;
	while (token[i])
	{
		free(token[i]);
		i++;
	}
	free(token);
}

void	free_redirections(t_redir *redir)
{
	t_redir	*redir_temp;

	while (redir)
	{
		redir_temp = redir;
		redir = redir->next;
		if (redir_temp->filename)
			free(redir_temp->filename);
		free(redir_temp);
	}
}

void	free_tokens(t_tokens *head)
{
	t_tokens	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free_token_array(temp->token);
		free_redirections(temp->redir);
		free(temp);
	}
}
