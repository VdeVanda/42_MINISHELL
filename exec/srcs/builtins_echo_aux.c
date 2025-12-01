/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo_aux.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 16:00:00 by vaires-m          #+#    #+#             */
/*   Updated: 2025/10/15 18:53:24 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	handle_escape_char(char c)
{
	if (c == 'n')
		ft_putchar_fd('\n', STDOUT_FILENO);
	else if (c == 't')
		ft_putchar_fd('\t', STDOUT_FILENO);
	else if (c == 'r')
		ft_putchar_fd('\r', STDOUT_FILENO);
	else if (c == 'b')
		ft_putchar_fd('\b', STDOUT_FILENO);
	else if (c == 'a')
		ft_putchar_fd('\a', STDOUT_FILENO);
	else if (c == 'v')
		ft_putchar_fd('\v', STDOUT_FILENO);
	else if (c == 'f')
		ft_putchar_fd('\f', STDOUT_FILENO);
	else if (c == '\\')
		ft_putchar_fd('\\', STDOUT_FILENO);
}

static int	is_valid_escape_char(char c)
{
	return (c == 'n' || c == 't' || c == 'r' || c == 'b' || c == 'a'
		|| c == 'v' || c == 'f' || c == '\\');
}

void	print_with_escapes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1])
		{
			if (is_valid_escape_char(str[i + 1]))
			{
				handle_escape_char(str[i + 1]);
			}
			else
			{
				ft_putchar_fd(str[i], STDOUT_FILENO);
				ft_putchar_fd(str[i + 1], STDOUT_FILENO);
			}
			i += 2;
		}
		else
		{
			ft_putchar_fd(str[i], STDOUT_FILENO);
			i++;
		}
	}
}

int	process_echo_flags(char **av, int *newline, int *escape_mode)
{
	int	i;

	*newline = 1;
	*escape_mode = 0;
	i = 1;
	while (av[i] && (is_n_flag(av[i]) || is_e_flag(av[i])))
	{
		if (is_n_flag(av[i]))
			*newline = 0;
		else if (is_e_flag(av[i]))
			*escape_mode = 1;
		i++;
	}
	return (i);
}

void	print_echo_args(char **av, int start_index, int escape_mode)
{
	int	i;

	i = start_index;
	while (av[i])
	{
		if (escape_mode)
			print_with_escapes(av[i]);
		else
			ft_putstr_fd(av[i], STDOUT_FILENO);
		if (av[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
}
