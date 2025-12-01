/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:58:14 by vabatist          #+#    #+#             */
/*   Updated: 2024/11/20 20:12:09 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
itoa allocates (with malloc(3)) and returns a string
representing the integer received as an argument.
Negative numbers must be handled.
Returns NULL if the allocation fails.
Parameters: n: The integer to be converted.
*/
static int	ft_size(int n)
{
	int	size;

	size = 0;
	if (n <= 0)
		size++;
	while (n)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	int			size;
	char		*str;
	long int	nb;

	nb = n;
	size = ft_size(nb);
	str = ft_calloc(size + 1, sizeof(char));
	if (!str)
		return (NULL);
	if (nb < 0)
		nb = -nb;
	while (size > 0)
	{
		str[--size] = (nb % 10) + '0';
		nb = nb / 10;
	}
	if (n < 0)
		str[0] = '-';
	if (n == 0)
		str[0] = '0';
	return (str);
}
/* int main(void)
{
    int n = -10000;
    char *str = ft_itoa(n);
    printf("str: %s\n", str);
    free(str);
    return (0);
} */