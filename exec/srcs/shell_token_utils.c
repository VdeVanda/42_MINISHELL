/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_token_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 19:40:00 by vaires-m          #+#    #+#             */
/*   Updated: 2025/09/27 13:45:22 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_list(t_envc *env)
{
	t_envc	*temp;

	while (env)
	{
		temp = env;
		env = env->next;
		if (temp->var)
			free(temp->var);
		if (temp->value)
			free(temp->value);
		free(temp);
	}
}
