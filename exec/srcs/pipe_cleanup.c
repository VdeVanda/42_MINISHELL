/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 16:00:00 by vaires-m          #+#    #+#             */
/*   Updated: 2025/10/26 18:20:14 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	cleanup_child_inherited_memory(void)
{
	t_shell	*shell;

	shell = get_shell();
	if (shell->arr_2d)
	{
		free_arr2(shell->arr_2d);
		shell->arr_2d = NULL;
	}
}
