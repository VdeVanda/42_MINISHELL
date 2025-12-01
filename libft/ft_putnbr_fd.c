/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 11:41:24 by vabatist          #+#    #+#             */
/*   Updated: 2024/11/16 12:08:48 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
putnbr_fd() transforms the integer n into a character string
and writes it to the file descriptor fd.
*/
void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	nb;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		nb = -1 * n;
	}
	else
	{
		nb = n;
	}
	if (nb >= 10)
	{
		ft_putnbr_fd(nb / 10, fd);
		nb = nb % 10;
	}
	if (nb < 10)
	{
		ft_putchar_fd(nb + '0', fd);
	}
}
/* int	main(void)
{
	int fd = open("Int_to_C.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

	ft_putnbr_fd(-2147483648, fd);
	ft_putchar_fd('\n', fd);
	ft_putnbr_fd(2147483647, fd);
	ft_putchar_fd('\n', fd);
	ft_putnbr_fd(0, fd);
	ft_putchar_fd('\n', fd);
	close(fd);
} */