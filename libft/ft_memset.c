/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:27:50 by vabatist          #+#    #+#             */
/*   Updated: 2024/11/16 11:27:44 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
memset: string.h
memset fills the first n bytes of the memory area pointed to by s
with the constant byte c.	
*/
void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)s;
	while (i < n)
	{
		str[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
/* int main() 
{
	char string[] = "Hello, World";
	printf("Before ft_memset: %s\n", string);
	ft_memset(string, 'x', 5);
	//memset(string, 'x', 5);
	printf("After ft_memset: %s\n", string);
	return 0;
} */