/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:07:22 by vabatist          #+#    #+#             */
/*   Updated: 2025/02/05 10:10:24 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr(char *str)
{
	int	counter;
	int	i;

	counter = 0;
	i = 0;
	if (!str)
		return (write(1, "(null)", 6));
	while (str[i])
	{
		counter += ft_putchar(str[i]);
		i++;
	}
	return (counter);
}

/* int	main(void)
{
	ft_putstr("Hello World!");
	ft_putchar('\n');
	ft_putstr("This is a test");
	ft_putchar('\n');
	ft_putstr("This is a test with a null pointer: ");
	ft_putstr(NULL);
	ft_putchar('\n');
} */