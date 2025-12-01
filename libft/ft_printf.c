/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 12:10:28 by vabatist          #+#    #+#             */
/*   Updated: 2025/02/05 10:10:52 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	loop(char c, va_list *args)
{
	if (c == 'c')
		return (ft_putchar(va_arg(*args, int)));
	else if (c == 's')
		return (ft_putstr(va_arg(*args, char *)));
	else if (c == 'd' || c == 'i')
		return (ft_putnbr(va_arg(*args, int)));
	else if (c == 'u')
		return (ft_putnbr(va_arg(*args, unsigned int)));
	else if (c == 'x')
		return (ft_print_hex(va_arg(*args, unsigned int), LC_HEX));
	else if (c == 'X')
		return (ft_print_hex(va_arg(*args, unsigned int), HC_HEX));
	else if (c == 'p')
		return (ft_print_ptr(va_arg(*args, unsigned long long)));
	else if (c == '%')
		return (ft_putchar('%'));
	return (0);
}

/*
printf: stdio.h
printf displays a formatted string on the screen.
*/
int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		counter;
	int		i;

	va_start(args, format);
	counter = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			counter += loop(format[i], &args);
		}
		else
			counter += ft_putchar(format[i]);
		i++;
	}
	va_end(args);
	return (counter);
}

/* int	main(void)
{
	ft_printf("Hello World!\n");
	printf("Hello World!\n");
	ft_printf("This is a test\n");
	printf("This is a test\n");
	ft_printf("This is a test with a null pointer: %s\n", NULL);
	printf("This is a test with a null pointer: %s\n", NULL);
	ft_printf("This is a test with a char: %c\n", 'c');
	printf("This is a test with a char: %c\n", 'c');
	ft_printf("This is a test with a string: %s\n", "string");
	printf("This is a test with a string: %s\n", "string");
	ft_printf("This is a test with a decimal: %d\n", 42);
	printf("This is a test with a decimal: %d\n", 42);
	ft_printf("This is a test with an intenger: %i\n", 42);
	printf("This is a test with an intenger: %i\n", 42);
	ft_printf("This is a test with an unsigned int: %u\n", 42);
	printf("This is a test with an unsigned int: %u\n", 42);
	ft_printf("This is a test with a hexadecimal: %x\n", 42);
	printf("This is a test with a hexadecimal: %x\n", 42);
	ft_printf("This is a test with a HEXADECIMAL: %X\n", 42);
	printf("This is a test with a HEXADECIMAL: %X\n", 42);
	ft_printf("This is a test with a pointer: %p\n", (void *)42);
	printf("This is a test with a pointer: %p\n", (void *)42);
	ft_printf("This is a test with a percent: %%\n");
	printf("This is a test with a percent: %%\n");
	return (0);
} */