/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 16:00:00 by vaires-m          #+#    #+#             */
/*   Updated: 2025/11/19 12:50:43 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_builtin_match(char *cmd, char *builtin, int len)
{
	return (ft_strncmp(cmd, builtin, len) == 0 && cmd[len] == '\0');
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (check_builtin_match(cmd, "echo", 4)
		|| check_builtin_match(cmd, "cd", 2)
		|| check_builtin_match(cmd, "pwd", 3)
		|| check_builtin_match(cmd, "export", 6)
		|| check_builtin_match(cmd, "unset", 5)
		|| check_builtin_match(cmd, "env", 3)
		|| check_builtin_match(cmd, "exit", 4));
}

static int	is_numeric_arg(char *s)
{
	int	i;

	if (!s || !s[0])
		return (0);
	i = 0;
	if (s[0] == '+' || s[0] == '-')
		i = 1;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (!ft_isdigit((unsigned char)s[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	print_numeric_error_and_exit(char *arg)
{
	ft_putstr_fd("exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	get_shell()->command_status = 2;
	g_signal_status = EXIT_WITH_CODE;
	return (0);
}

int	exit_builtin(char **av)
{
	int	exit_code;

	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (!av[1])
	{
		get_shell()->command_status = 0;
		g_signal_status = EXIT_NORMAL;
		return (0);
	}
	if (!is_numeric_arg(av[1]))
		return (print_numeric_error_and_exit(av[1]));
	if (av[2])
	{
		write(STDERR_FILENO, "exit: too many arguments\n", 25);
		return (1);
	}
	exit_code = ft_atoi(av[1]);
	get_shell()->command_status = (unsigned char)exit_code;
	g_signal_status = EXIT_WITH_CODE;
	return (0);
}
