/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 20:45:00 by vaires-m          #+#    #+#             */
/*   Updated: 2025/10/29 12:19:14 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

static char	*try_path_directory(char *dir, char *cmd)
{
	char	*full_path;

	full_path = build_path(dir, cmd);
	if (full_path && access(full_path, X_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}

char	*search_in_path_dirs(char **path_dirs, char *cmd)
{
	char	*full_path;
	int		i;

	if (!path_dirs)
		return (NULL);
	i = -1;
	while (path_dirs[++i])
	{
		full_path = try_path_directory(path_dirs[i], cmd);
		if (full_path)
		{
			free_split(path_dirs);
			return (full_path);
		}
	}
	free_split(path_dirs);
	return (NULL);
}

char	**get_path_dirs(void)
{
	char	*path_env;
	char	**path_dirs;

	path_env = ft_get_env("PATH");
	if (!path_env)
		return (NULL);
	path_dirs = ft_split(path_env, ':');
	free(path_env);
	return (path_dirs);
}

static int	is_directory(char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (0);
	return (S_ISDIR(path_stat.st_mode));
}

char	*check_absolute_path(char *cmd)
{
	if (!cmd)
		return (NULL);
	if (access(cmd, F_OK) == 0)
	{
		if (is_directory(cmd))
		{
			ft_putstr_fd(cmd, STDERR_FILENO);
			ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
			return (NULL);
		}
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		else
		{
			ft_putstr_fd(cmd, STDERR_FILENO);
			ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
			return (NULL);
		}
	}
	return (NULL);
}
