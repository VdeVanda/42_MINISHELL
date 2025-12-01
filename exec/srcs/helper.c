/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 16:00:00 by vaires-m          #+#    #+#             */
/*   Updated: 2025/10/01 12:16:33 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator(char *token)
{
	if (!token)
		return (0);
	if (ft_strncmp(token, "|", 2) == 0
		|| ft_strncmp(token, ">>", 3) == 0
		|| ft_strncmp(token, "<<", 3) == 0
		|| ft_strncmp(token, ">", 2) == 0
		|| ft_strncmp(token, "<", 2) == 0)
		return (1);
	return (0);
}

int	find_env_index(char **envp, char *name)
{
	int	i;
	int	len;

	if (!envp || !name)
		return (-1);
	i = 0;
	len = ft_strlen(name);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}
