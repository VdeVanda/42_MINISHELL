/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:39:36 by vabatist          #+#    #+#             */
/*   Updated: 2024/11/23 10:09:48 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
atoi: stdlib.h
atoi converts a string to an int.
It skips leading whitespace, considers only one sign ('+' or '-'), 
and converts the subsequent digits.
*/
int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	nb;

	i = 0;
	sign = 1;
	nb = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
	{
		i++;
	}
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (nb * sign);
}
/* int	main(void)
{
	char *test1 = "   ---+--+1234ab567";
	char *test2 = "   +42";
	char *test3 = "   -42";
	char *test4 = "   -+--+42";
	char *test5 = "   123abc456";
	char *test6 = "   0";
	char *test7 = "   -0000012345";
	
	printf("ft_atoi(\"%s\") = %d\n", test1, ft_atoi(test1));
	printf("ft_atoi(\"%s\") = %d\n", test2, ft_atoi(test2));
	printf("ft_atoi(\"%s\") = %d\n", test3, ft_atoi(test3));
	printf("ft_atoi(\"%s\") = %d\n", test4, ft_atoi(test4));
	printf("ft_atoi(\"%s\") = %d\n", test5, ft_atoi(test5));
	printf("ft_atoi(\"%s\") = %d\n", test6, ft_atoi(test6));
	printf("ft_atoi(\"%s\") = %d\n", test7, ft_atoi(test7));
	printf("ft_atoi(\"%s\") = %d\n", test4, atoi(test4));
	return (0);
}  */