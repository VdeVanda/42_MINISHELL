/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:23:00 by vabatist          #+#    #+#             */
/*   Updated: 2024/11/16 11:17:41 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
isalpha: ctype.h
isalpha checks if a character is an alphabetic character (letter).
*/
int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}
/* 
#include <stdio.h>

int	main(void)
{
	printf("%d\n", ft_isalpha('v'));
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc < 2)
	{
		printf("Preciso de um argumento");
		return (1);
	}
	printf("%d\n", ft_isalpha('\0'));
	printf("%d\n", isaplha('\0));
	return (0);
} */