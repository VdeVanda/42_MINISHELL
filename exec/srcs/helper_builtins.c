/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 16:00:00 by vaires-m          #+#    #+#             */
/*   Updated: 2025/10/01 12:36:56 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_env_string(char *name, char *value)
{
	char	*result;
	char	*temp;

	temp = ft_strjoin(name, "=");
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, value);
	free(temp);
	return (result);
}

int	count_env(char **envp)
{
	int	i;

	if (!envp)
		return (0);
	i = 0;
	while (envp[i])
		i++;
	return (i);
}

static int	validate_name_chars(char *name)
{
	int	i;

	i = 1;
	while (name[i])
	{
		if (!ft_isalpha(name[i]) && !ft_isdigit(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_name(char *name)
{
	if (!name)
		return (0);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (0);
	return (validate_name_chars(name));
}

char	**add_new_var(char **envp, char *name, char *value)
{
	int		count;
	char	**new_envp;
	int		i;

	if (!envp || !name || !value)
		return (envp);
	count = count_env(envp);
	new_envp = malloc(sizeof(char *) * (count + 2));
	if (!new_envp)
		return (envp);
	i = -1;
	while (++i < count)
		new_envp[i] = ft_strdup(envp[i]);
	new_envp[count] = create_env_string(name, value);
	new_envp[count + 1] = NULL;
	return (new_envp);
}
