/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 16:00:00 by vaires-m          #+#    #+#             */
/*   Updated: 2025/09/27 13:32:36 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_env_from_node(t_envc *env_node)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(env_node->var, "=");
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, env_node->value);
	free(temp);
	return (result);
}
