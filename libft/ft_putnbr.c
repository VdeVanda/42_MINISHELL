/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:07:35 by vabatist          #+#    #+#             */
/*   Updated: 2025/02/05 10:10:34 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_putnbr(long n)
{
	long	nb;
	long	counter;

	nb = n;
	counter = 0;
	if (nb < 0)
	{
		counter += ft_putchar('-');
		nb = -nb;
	}
	if (nb <= 9)
	{
		counter += ft_putchar(nb + '0');
	}
	else
	{
		counter += ft_putnbr(nb / 10);
		counter += ft_putnbr(nb % 10);
	}
	return (counter);
}
/* int	main(void)
{
	ft_putnbr(-2147483648);
	ft_putchar('\n');
	ft_putnbr(2147483647);
	ft_putchar('\n');
	ft_putnbr(0);
	ft_putchar('\n');
} */