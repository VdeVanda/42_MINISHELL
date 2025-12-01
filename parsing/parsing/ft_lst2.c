/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:55:27 by vabatist          #+#    #+#             */
/*   Updated: 2025/09/10 16:53:05 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @file ft_lst2.c
 * @brief Functions to manage the linked list of redirection nodes.
 *
 * This file contains functions to manage the linked list of redirection nodes
 * created during the parsing of shell commands for handling
 * input/output redirections.
 */

/**
 * @brief Creates a new redirection node and initializes its fields.
 *
 * This function is used to build the linked list of redirections
 * that represent the parsed redirection commands. It allocates memory
 * for a new redirection node and initializes it to default values.
 *
 * @return A pointer to the newly created redirection node, or NULL on failure
 */
t_redir	*lst_redir(void)
{
	t_redir	*redir;

	redir = ft_calloc(sizeof(t_redir), 1);
	if (!redir)
		return (NULL);
	redir->next = NULL;
	return (redir);
}

/**
 * @brief Adds a new redirection node to the back of the redirection list.
 *
 * It traverses the list to find the last node and appends the new node.
 * If the list is empty, it sets the head to the new node. The function handles
 *
 * @param lst Pointer to the head of the redirection list
 * @param new The new redirection node to add
 */
void	ft_lstadd_back_redir(t_redir **lst, t_redir *new)
{
	t_redir	*temp;

	if (!new || !lst)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}
