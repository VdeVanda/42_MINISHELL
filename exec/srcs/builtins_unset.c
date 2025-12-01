/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 16:00:00 by vaires-m          #+#    #+#             */
/*   Updated: 2025/10/09 13:11:28 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	shift_env_array(char **envp, int var_index)
{
	int	j;

	free(envp[var_index]);
	j = var_index;
	while (envp[j + 1])
	{
		envp[j] = envp[j + 1];
		j++;
	}
	envp[j] = NULL;
}

static void	remove_from_env_list(char *var_name)
{
	t_envc	*env;
	t_envc	*prev;

	env = get_shell()->env;
	prev = NULL;
	while (env)
	{
		if (ft_strcmp(env->var, var_name) == 0)
		{
			if (prev)
				prev->next = env->next;
			else
				get_shell()->env = env->next;
			free(env->var);
			free(env->value);
			free(env);
			break ;
		}
		prev = env;
		env = env->next;
	}
}

char	**unset_builtin(char **av, char **envp)
{
	int	i;
	int	var_index;

	if (!av[1])
		return (envp);
	i = 1;
	while (av[i])
	{
		var_index = find_env_index(envp, av[i]);
		if (var_index >= 0)
		{
			shift_env_array(envp, var_index);
			remove_from_env_list(av[i]);
		}
		i++;
	}
	return (envp);
}
