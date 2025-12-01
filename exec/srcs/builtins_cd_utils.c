/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 16:00:00 by vaires-m          #+#    #+#             */
/*   Updated: 2025/11/28 19:04:39 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_tilde_path(char *path)
{
	char	*home;
	char	*expanded;

	home = ft_get_env("HOME");
	if (!home)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
		return (NULL);
	}
	if (path[1] == '\0')
		return (home);
	expanded = ft_strjoin(home, &path[1]);
	return (expanded);
}

char	*handle_dash_argument(void)
{
	char	*oldpwd;

	oldpwd = ft_get_env("OLDPWD");
	if (!oldpwd)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR_FILENO);
		return (NULL);
	}
	ft_putstr_fd(oldpwd, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	return (oldpwd);
}

void	free_path_if_needed(char *path, char **av)
{
	char	*home;

	home = ft_get_env("HOME");
	if (path != av[1] && home && ft_strncmp(path, home, ft_strlen(home)) != 0)
	{
		free(path);
		free(home);
	}
	else if (home)
		free(home);
}

char	*get_cd_path(char **av)
{
	char	*home;

	if (!av[1])
	{
		home = ft_get_env("HOME");
		if (!home)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
			return (NULL);
		}
		return (home);
	}
	if (av[1][0] == '\0')
		return (ft_strdup("."));
	if (ft_strcmp(av[1], "-") == 0)
		return (handle_dash_argument());
	if (av[1][0] == '~')
		return (expand_tilde_path(av[1]));
	return (av[1]);
}

int	handle_cd_error(char **av, int result)
{
	if (result != 0)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		if (av[1])
			perror(av[1]);
		else
			perror("HOME");
		return (1);
	}
	return (0);
}
