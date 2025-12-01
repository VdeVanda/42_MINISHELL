/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:26:28 by vabatist          #+#    #+#             */
/*   Updated: 2024/11/23 10:01:24 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* 
memmove: string.h
memmove copies 'n' bytes from 'src' to 'dest'
*/
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (((unsigned char *)dest) < ((unsigned char *)src))
		return (ft_memcpy(dest, src, n));
	else
	{
		while (n > 0)
		{
			n--;
			((unsigned char *)dest)[n] = ((unsigned char *)src)[n];
		}
	}
	return (dest);
}
/* int	main(void)
{
	char src[] = "hello, ";
	char dest[] = "       mundo!";
	ft_memmove(dest, src, 7);
	memmove(dest, src, 7);
	printf("%s\n", dest);
} */