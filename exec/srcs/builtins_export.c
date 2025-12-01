/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 20:30:00 by vaires-m          #+#    #+#             */
/*   Updated: 2025/11/12 11:20:50 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	export_has_split_args(char **argv)
{
	(void)argv;
	return (0);
}

static char	**handle_split_export(char **envp, char **argv)
{
	char	*var_name;
	char	*var_value;
	char	**new_envp;

	var_name = extract_var_name(argv[1]);
	if (!var_name || !is_valid_name(var_name))
	{
		print_export_error(argv[1]);
		free(var_name);
		return (envp);
	}
	var_value = reconstruct_var_value(argv);
	new_envp = update_environment(envp, var_name, var_value);
	free(var_name);
	free(var_value);
	return (new_envp);
}

static char	**process_export_args(char **envp, char **argv)
{
	int		i;
	char	**new_envp;

	i = 0;
	new_envp = envp;
	if (export_has_split_args(argv))
		return (handle_split_export(new_envp, argv));
	while (argv[++i])
		new_envp = process_single_export(new_envp, argv[i]);
	return (new_envp);
}

char	**export_builtin(char **envp, char **argv)
{
	char	**new_envp;

	new_envp = envp;
	if (!argv[1])
	{
		print_export(envp);
		return (envp);
	}
	return (process_export_args(new_envp, argv));
}
