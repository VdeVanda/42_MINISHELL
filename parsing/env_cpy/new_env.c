/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 12:50:45 by vabatist          #+#    #+#             */
/*   Updated: 2025/09/10 16:44:32 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @file new_env.c
 * @brief Functions to create and manage a linked list of environment variables.
 * This file contains functions to create a new linked list of environment
 * variables  * from an array of strings, where each string is
 * in the format "VAR=VALUE".
 * It includes functions to extract the variable name and value,
 * create new nodes, and add them to the list.
 * The linked list structure allows for dynamic management
 * of environment variables within the shell environment.
 */

/**
 * @brief Extracts the variable name from an environment string.
 * This function takes an environment string in the format "VAR=VALUE"
 * and extracts the variable name (VAR) part.
 * It allocates memory for the new string and returns it.
 * If the input string does not contain an '=',
 * it returns the entire string as the variable name.
 * @param env The environment string to process
 * @return A newly allocated string containing the variable name,
 * or NULL on memory allocation failure
 * @note The caller is responsible for freeing the returned string.
 * @note If the input string is NULL, the function returns NULL.
 */
static char	*ft_env_var(char *env)
{
	int		i;
	char	*var;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	var = (char *)malloc(sizeof(char) * (i + 1));
	if (!var)
		return (NULL);
	i = 0;
	while (env[i] && env[i] != '=')
	{
		var[i] = env[i];
		i++;
	}
	var[i] = '\0';
	return (var);
}

/**
 * @brief Extracts the value from an environment string.
 * This function takes an environment string in the format "VAR=VALUE"
 * and extracts the value (VALUE) part.
 * It allocates memory for the new string and returns it.
 * If the input string does not contain an '=', it returns an empty
 * string as the value.
 * @param env The environment string to process
 * @return A newly allocated string containing the value, or NULL
 * on memory allocation failure
 * @note The caller is responsible for freeing the returned string.
 * @note If the input string is NULL, the function returns NULL.
 * @note If there is no value part, the function returns an empty string.
 */
static char	*ft_env_value(char *env)
{
	int		i;
	int		value_len;
	char	*value;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	if (!env[i] || env[i + 1] == '\0')
		return (ft_strdup(""));
	value_len = ft_strlen(env) - (i + 1);
	value = (char *)malloc(sizeof(char) * (value_len + 1));
	if (!value)
		return (NULL);
	i++;
	ft_strlcpy(value, &env[i], value_len + 1);
	return (value);
}

/**
 * @brief Creates a new environment variable node.
 * This function allocates memory for a new environment variable node,
 * initializes its fields using the provided environment string,
 * and returns a pointer to the new node.
 * If memory allocation fails, it returns NULL.
 * @param env The environment string in the format "VAR=VALUE"
 * @return A pointer to the newly created environment variable node,
 * or NULL on failure
 * @note The caller is responsible for freeing the returned node and its fields.
 * @note If the input string is NULL, the function returns NULL.
 * @note The 'visible' field is initialized to 1 (true) by default.
 * @note The 'next' pointer is initialized to NULL.
 */
static t_envc	*ft_lstnew_env(char *env)
{
	t_envc	*new;

	new = malloc(sizeof(t_envc));
	if (!new)
		return (NULL);
	new->var = ft_env_var(env);
	if (!new->var)
	{
		free(new);
		return (NULL);
	}
	new->value = ft_env_value(env);
	if (!new->value)
	{
		free(new->var);
		free(new);
		return (NULL);
	}
	new->visible = 1;
	new->next = NULL;
	return (new);
}

/**
 * @brief Adds a new environment variable node to the end of the list.
 * If the list is empty, it sets the head to the new node.
 * If memory allocation for the new node fails, it does nothing.
 * @param env_new Pointer to the head of the environment variable list
 * @param env The environment string in the format "VAR=VALUE" to add
 * @return void
 * @note If the input string is NULL, the function does nothing.
 * @note The function handles NULL pointers gracefully by returning early
 * if invalid parameters are provided.
 */
void	ft_lstadd_back_env(t_envc **env_new, char *env)
{
	t_envc	*temp;
	t_envc	*new;

	if (!env_new || !env)
		return ;
	new = ft_lstnew_env(env);
	if (!new)
		return ;
	if (!(*env_new))
	{
		*env_new = new;
		return ;
	}
	temp = *env_new;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

/**
 * @brief Creates a linked list of environment variables from an array
 * of strings.
 * This function takes an array of environment strings
 * (in the format "VAR=VALUE")
 * and creates a linked list of environment variable nodes.
 * It iterates through the array, creating and adding each node to the list.
 * If the input array is NULL, it returns NULL.
 * @param env The array of environment strings to process
 * @param env_new Pointer to the head of the environment variable list
 * @return A pointer to the head of the newly created environment variable list,
 * or NULL if input is NULL
 * @note The caller is responsible for managing the memory of the list
 * and its nodes.
 * @note If memory allocation for any node fails, the function
 * continues processing the remaining strings.
 * @note The function handles NULL pointers gracefully by returning NULL
 * if the input array is NULL.
 * @note The 'next' pointer of each new node is initialized to NULL
 * in ft_lstnew_env.
 * @note The 'visible' field of each new node is initialized to 1 (true)
 * in ft_lstnew_env.
 */
t_envc	*ft_env_cpy(char **env, t_envc *env_new)
{
	int	i;

	i = 0;
	if (env == NULL)
		return (NULL);
	while (env[i] != NULL)
	{
		ft_lstadd_back_env(&env_new, env[i]);
		i++;
	}
	return (env_new);
}
