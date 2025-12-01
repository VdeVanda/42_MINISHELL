/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 12:07:42 by vabatist          #+#    #+#             */
/*   Updated: 2025/02/05 10:10:57 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>
#include <stdio.h>

/*
The unsigned long long type is used to ensure that the function
can handle the full range of pointer values, which are typically 64-bit.
This ensures that all pointer values, regardless of their size, can be
correctly represented and printed.
*/
int	ft_print_ptr(unsigned long long ptr)
{
	int	counter;

	counter = 0;
	if (ptr == 0)
		counter += (ft_putstr("(nil)"));
	else
	{
		counter += ft_putstr("0x");
		counter += ft_print_hex(ptr, LC_HEX);
	}
	return (counter);
}
/* int main(void)
{
	// ft_print_ptr(0);
	// ft_putchar('\n');
	// ft_print_ptr(2147483647);
	// ft_putchar('\n');
	// ft_print_ptr(0);
	// ft_putchar('\n');
	// ft_print_ptr(42);
	// ft_putchar('\n');

	// printf(" %p ", (void *)-1);
	// ft_print_ptr(" %p ", (void *)-1);
	// write (1, "\n", 1);
	// printf(" %p %p ", (void *)LONG_MIN, (void *)LONG_MAX);
	// ft_print_ptr(" %p %p ", (void *)LONG_MIN, (void *)LONG_MAX);
	// write (1, "\n", 1);
	// printf(" %p %p ", (void *)INT_MIN, (void *)INT_MAX);
	// ft_print_ptr(" %p %p ", (void *)INT_MIN, (void *)INT_MAX);
	// write (1, "\n", 1);
	// printf(" %p %p ", (void *)ULONG_MAX, (void *)-ULONG_MAX);
	// ft_print_ptr(" %p %p ", (void *)ULONG_MAX, (void *)-ULONG_MAX);
	// write (1, "\n", 1);

	// printf(" %p ", (void *)-1);
	// write (1, "\n", 1);
	// ft_print_ptr((unsigned long long)(void *)-1);
	// write (1, "\n", 1);
	// write (1, "\n", 1);
	// printf(" %p %p ", (void *)LONG_MIN, (void *)LONG_MAX);
	// write (1, "\n", 1);
	// ft_print_ptr((unsigned long long)(void *)LONG_MIN);
	// write (1, " ", 1);
	// ft_print_ptr((unsigned long long)(void *)LONG_MAX);
	// write (1, "\n", 1);
	// write (1, "\n", 1);

	// printf(" %p %p ", (void *)INT_MIN, (void *)INT_MAX);
	// write (1, "\n", 1);
	// ft_print_ptr((unsigned long long)(void *)INT_MIN);
	// write (1, " ", 1);
	// ft_print_ptr((unsigned long long)(void *)INT_MAX);
	// write (1, "\n", 1);
	// write (1, "\n", 1);

	// printf(" %p %p ", (void *)ULONG_MAX, (void *)-ULONG_MAX);
	// write (1, "\n", 1);
	// ft_print_ptr((unsigned long long)(void *)ULONG_MAX);
	// write (1, " ", 1);
	// ft_print_ptr((unsigned long long)(void *)-ULONG_MAX);
	// write (1, "\n", 1);
} */