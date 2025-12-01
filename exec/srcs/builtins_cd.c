/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 20:30:00 by vaires-m          #+#    #+#             */
/*   Updated: 2025/10/29 15:50:45 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_pwd_variables(char *cwd, char *new_cwd)
{
	t_shell	*shell;

	shell = get_shell();
	shell->env_arr = update_environment(shell->env_arr, "OLDPWD", cwd);
	shell->env_arr = update_environment(shell->env_arr, "PWD", new_cwd);
	ft_lstclear_env(&shell->env);
	shell->env = ft_env_cpy(shell->env_arr, NULL);
	return (0);
}

static int	get_new_cwd(char **new_cwd)
{
	*new_cwd = getcwd(NULL, 0);
	if (!*new_cwd)
	{
		perror("getcwd");
		return (1);
	}
	return (0);
}

static int	execute_cd_change(char **av)
{
	char	cwd[1024];
	char	*path;
	char	*new_cwd;
	int		result;

	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("getcwd");
		return (1);
	}
	path = get_cd_path(av);
	if (!path)
		return (1);
	result = chdir(path);
	free_path_if_needed(path, av);
	if (handle_cd_error(av, result) != 0)
		return (1);
	if (get_new_cwd(&new_cwd) != 0)
		return (1);
	update_pwd_variables(cwd, new_cwd);
	free(new_cwd);
	return (0);
}

int	cd_builtin(char **av)
{
	return (execute_cd_change(av));
}
