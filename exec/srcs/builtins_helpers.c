/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 16:00:00 by vaires-m          #+#    #+#             */
/*   Updated: 2025/11/19 14:05:43 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_var_name(char *arg)
{
	char	*equals_pos;

	equals_pos = ft_strchr(arg, '=');
	if (!equals_pos)
		return (ft_strdup(arg));
	return (ft_substr(arg, 0, equals_pos - arg));
}

char	*reconstruct_var_value(char **argv)
{
	char	*var_value;
	char	*temp;
	int		j;

	var_value = ft_strdup(ft_strchr(argv[1], '=') + 1);
	j = 2;
	while (argv[j])
	{
		temp = ft_strjoin(var_value, " ");
		free(var_value);
		var_value = temp;
		temp = ft_strjoin(var_value, argv[j]);
		free(var_value);
		var_value = temp;
		j++;
	}
	return (var_value);
}

static char	*extract_export_value(char *equals_pos)
{
	return (ft_strdup(equals_pos + 1));
}

static int	validate_export_args(char *var_name, char *var_value, char *arg)
{
	if (!var_name || !is_valid_name(var_name))
	{
		print_export_error(arg);
		free(var_name);
		free(var_value);
		return (0);
	}
	return (1);
}

char	**process_single_export(char **envp, char *arg)
{
	char	*equals_pos;
	char	*var_name;
	char	*var_value;
	char	**new_envp;

	equals_pos = ft_strchr(arg, '=');
	if (!equals_pos)
	{
		if (!is_valid_name(arg))
			print_export_error(arg);
		return (envp);
	}
	var_name = ft_substr(arg, 0, equals_pos - arg);
	var_value = extract_export_value(equals_pos);
	if (!validate_export_args(var_name, var_value, arg))
		return (envp);
	new_envp = update_environment(envp, var_name, var_value);
	free(var_name);
	free(var_value);
	return (new_envp);
}
