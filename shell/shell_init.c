/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:00:00 by vaires-m          #+#    #+#             */
/*   Updated: 2025/10/07 23:06:45 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

volatile sig_atomic_t	g_signal_status;

int	init_shell(t_shell *shell, char **envp)
{
	shell->tokens = NULL;
	shell->arr_2d = NULL;
	shell->command_status = 0;
	shell->has_and_operator = 0;
	shell->env = ft_env_cpy(envp, NULL);
	shell->env_arr = env_to_array(shell->env);
	if (!shell->env || !shell->env_arr)
	{
		ft_putstr_fd("Error: Failed to initialize environment\n",
			STDERR_FILENO);
		return (1);
	}
	return (0);
}

void	cleanup_shell(t_shell *shell)
{
	if (shell->env)
		ft_lstclear_env(&shell->env);
	if (shell->env_arr)
		free_environment(shell->env_arr);
	if (shell->tokens)
		free_tokens(shell->tokens);
	if (shell->arr_2d)
		free_arr2(shell->arr_2d);
	clear_history();
}
