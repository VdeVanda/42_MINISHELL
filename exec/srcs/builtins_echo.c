/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 20:30:00 by vaires-m          #+#    #+#             */
/*   Updated: 2025/11/19 14:21:23 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_n_flag(char *str)
{
	int	i;

	if (!str || str[0] != '-' || str[1] != 'n')
		return (0);
	i = 2;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	is_e_flag(char *str)
{
	return (str && ft_strcmp(str, "-e") == 0);
}

int	echo_builtin(char **av)
{
	int	start_index;
	int	newline;
	int	escape_mode;

	start_index = process_echo_flags(av, &newline, &escape_mode);
	print_echo_args(av, start_index, escape_mode);
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
