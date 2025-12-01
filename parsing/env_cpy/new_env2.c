/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_env2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:03:46 by vabatist          #+#    #+#             */
/*   Updated: 2025/09/10 16:38:28 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Clears the linked list of environment variables.
 * This function iterates through the linked list of environment variables,
 * freeing each node's allocated memory for the variable name,
 * value, and the node itself.
 * After freeing all nodes, it sets the head pointer to NULL.
 * @param env_new Pointer to the head of the environment variable list
 * @return void
 */
void	ft_lstclear_env(t_envc **env_new)
{
	t_envc	*temp;

	while (*env_new)
	{
		temp = (*env_new)->next;
		free((*env_new)->var);
		if ((*env_new)->value)
			free((*env_new)->value);
		free(*env_new);
		*env_new = temp;
	}
}

/**
 * @brief debug only!!! Prints the linked list of environment variables.
 * This function iterates through the linked list of environment variables
 * and prints each variable's name, value, and visibility status.
 * it is useful for debugging and verifying the contents of the environment list.
 * @param env Pointer to the head of the environment variable list
 * @return void
 */
void	print_env_list(t_envc *env)
{
	while (env)
	{
		printf("var: %s, value: %s, visible: %d\n", env->var, env->value,
			env->visible);
		env = env->next;
	}
}
