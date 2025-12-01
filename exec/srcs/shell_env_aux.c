/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_env_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 16:00:00 by vaires-m          #+#    #+#             */
/*   Updated: 2025/10/23 16:00:00 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_env_vars(char *env_str, t_envc *new_node)
{
	char	*equal_pos;

	equal_pos = ft_strchr(env_str, '=');
	if (equal_pos)
	{
		*equal_pos = '\0';
		new_node->var = ft_strdup(env_str);
		new_node->value = ft_strdup(equal_pos + 1);
		*equal_pos = '=';
	}
	else
	{
		new_node->var = ft_strdup(env_str);
		new_node->value = ft_strdup("");
	}
	return (new_node->var && new_node->value);
}

t_envc	*create_env_node(char *env_str)
{
	t_envc	*new_node;

	new_node = malloc(sizeof(t_envc));
	if (!new_node)
		return (NULL);
	if (!parse_env_vars(env_str, new_node))
	{
		free(new_node->var);
		free(new_node->value);
		free(new_node);
		return (NULL);
	}
	new_node->visible = 1;
	new_node->next = NULL;
	return (new_node);
}

void	add_env_node_to_list(t_envc **env_list, t_envc *new_node)
{
	t_envc	*current;

	if (!*env_list)
		*env_list = new_node;
	else
	{
		current = *env_list;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
}

int	count_visible_env(t_envc *env)
{
	t_envc	*current;
	int		count;

	current = env;
	count = 0;
	while (current)
	{
		if (current->visible)
			count++;
		current = current->next;
	}
	return (count);
}
