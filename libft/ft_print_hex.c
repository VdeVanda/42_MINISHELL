/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 11:21:04 by vabatist          #+#    #+#             */
/*   Updated: 2025/02/05 10:11:05 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_hex(unsigned int long nb, char *hex)
{
	int	counter;

	counter = 0;
	if (nb < 16)
	{
		counter += ft_putchar(hex[nb]);
	}
	else
	{
		counter += ft_print_hex(nb / 16, hex);
		counter += ft_print_hex(nb % 16, hex);
	}
	return (counter);
}

/* int	main(void)
{
	ft_print_hex(2147483647, "0123456789abcdef");
	ft_putchar('\n');
	ft_print_hex(2147483647, "0123456789ABCDEF");
	ft_putchar('\n');
	ft_print_hex(0, "0123456789abcdef");
	ft_putchar('\n');
	ft_print_hex(0, "0123456789ABCDEF");
	ft_putchar('\n');
} */