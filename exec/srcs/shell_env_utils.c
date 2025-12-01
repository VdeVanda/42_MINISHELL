/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_env_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 19:40:00 by vaires-m          #+#    #+#             */
/*   Updated: 2025/09/27 13:42:28 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cleanup_env_array(char **env_array, int count)
{
	int	j;

	j = 0;
	while (j < count)
	{
		free(env_array[j]);
		j++;
	}
	free(env_array);
}

t_envc	*init_env(char **envp)
{
	t_envc	*env_list;
	t_envc	*new_node;
	int		i;

	env_list = NULL;
	i = 0;
	while (envp[i])
	{
		new_node = create_env_node(envp[i]);
		if (!new_node)
		{
			ft_lstclear_env(&env_list);
			return (NULL);
		}
		add_env_node_to_list(&env_list, new_node);
		i++;
	}
	return (env_list);
}

static int	fill_env_array(t_envc *env, char **env_array, int count)
{
	t_envc	*current;
	int		i;

	current = env;
	i = 0;
	while (current && i < count)
	{
		if (current->visible)
		{
			env_array[i] = create_env_from_node(current);
			if (!env_array[i])
			{
				cleanup_env_array(env_array, i);
				return (0);
			}
			i++;
		}
		current = current->next;
	}
	return (1);
}

char	**env_to_array(t_envc *env)
{
	char	**env_array;
	int		count;

	count = count_visible_env(env);
	env_array = malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return (NULL);
	if (!fill_env_array(env, env_array, count))
		return (NULL);
	env_array[count] = NULL;
	return (env_array);
}
