/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 16:00:00 by vaires-m          #+#    #+#             */
/*   Updated: 2025/10/07 15:50:43 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell		*shell;

	(void)argc;
	(void)argv;
	g_signal_status = 0;
	handle_sig(PARENT);
	shell = get_shell();
	if (init_shell(shell, envp) != 0)
		return (1);
	ft_putstr_fd("Welcome to minishell with integrated parsing!\n",
		STDOUT_FILENO);
	return (main_loop(shell));
}
