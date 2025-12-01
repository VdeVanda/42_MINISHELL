/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_helpers2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 16:00:00 by vaires-m          #+#    #+#             */
/*   Updated: 2025/09/26 21:14:25 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**update_environment(char **envp, char *name, char *value)
{
	int		var_index;
	char	**new_envp;

	var_index = find_env_index(envp, name);
	if (var_index >= 0)
	{
		free(envp[var_index]);
		envp[var_index] = create_env_string(name, value);
		return (envp);
	}
	new_envp = add_new_var(envp, name, value);
	if (new_envp != envp)
		free_environment(envp);
	return (new_envp);
}

void	print_export_error(char *arg)
{
	ft_putstr_fd("export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

void	print_export_no_value_error(char *arg)
{
	ft_putstr_fd("export: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": variable exported without value\n", STDERR_FILENO);
}
