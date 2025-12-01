/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 16:00:00 by vaires-m          #+#    #+#             */
/*   Updated: 2025/11/12 11:20:50 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_builtin(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
	{
		ft_putstr_fd(cwd, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (0);
	}
	perror("pwd");
	return (1);
}

int	env_builtin(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return (1);
	while (envp[i])
	{
		ft_putstr_fd(envp[i], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		i++;
	}
	return (0);
}

static void	print_export_var(char *env_var)
{
	char	*equals;

	equals = ft_strchr(env_var, '=');
	if (equals)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		write(STDOUT_FILENO, env_var, equals - env_var);
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(equals + 1, STDOUT_FILENO);
		ft_putstr_fd("\"\n", STDOUT_FILENO);
	}
	else
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(env_var, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
}

int	print_export(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return (1);
	while (envp[i])
	{
		print_export_var(envp[i]);
		i++;
	}
	return (0);
}
