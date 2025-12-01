/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 19:30:00 by vaires-m          #+#    #+#             */
/*   Updated: 2025/10/01 12:38:09 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**dispatch_builtin(char **av, char **my_envp, int *status)
{
	if (ft_strcmp(av[0], "echo") == 0)
		return (*status = echo_builtin(av), my_envp);
	else if (ft_strcmp(av[0], "cd") == 0)
		return (*status = cd_builtin(av), my_envp);
	else if (ft_strcmp(av[0], "pwd") == 0)
		return (*status = pwd_builtin(), my_envp);
	else if (ft_strcmp(av[0], "export") == 0)
		return (handle_export_builtin(av, my_envp, status));
	else if (ft_strcmp(av[0], "unset") == 0)
		return (*status = 0, unset_builtin(av, my_envp));
	else if (ft_strcmp(av[0], "env") == 0)
		return (*status = env_builtin(my_envp), my_envp);
	else if (ft_strcmp(av[0], "exit") == 0)
		return (*status = exit_builtin(av), my_envp);
	*status = 127;
	return (my_envp);
}

char	**handle_export_builtin(char **av, char **my_envp, int *status)
{
	char	**new_env;

	(void)my_envp;
	*status = 0;
	new_env = export_builtin(get_shell()->env_arr, av);
	get_shell()->env_arr = new_env;
	ft_lstclear_env(&get_shell()->env);
	get_shell()->env = ft_env_cpy(new_env, NULL);
	return (new_env);
}
