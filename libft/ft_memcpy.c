/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:22:59 by vabatist          #+#    #+#             */
/*   Updated: 2024/11/13 09:06:03 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* 
memcpy: string.h
copies 'n' bytes from 'src', into 'dest'
*/
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

/* 
int	main(void)
{
	char	src[] = "hello";
	char	dest[] = "mundo";
	ft_memcpy(dest, src, 3);
	memcpy(dest, src, 3);
	printf("%s\n", dest);
}
*/