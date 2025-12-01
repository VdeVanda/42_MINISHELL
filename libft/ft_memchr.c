/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 11:53:38 by vabatist          #+#    #+#             */
/*   Updated: 2024/11/09 12:59:50 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
memchr: string.h
memchr check the 'n' bytes in 's' until it finds c. If there is no match,
it returns NULL, if not, it returns the memory address
*/
void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*copy_s;
	unsigned char	copy_c;
	size_t			i;

	copy_s = (unsigned char *)s;
	copy_c = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (copy_s[i] == copy_c)
			return ((void *)(s + i));
		i++;
	}
	return (NULL);
}
/*
int	main(void)
{
	const char	s[] = "hello, world";

	printf("my ft: %s\n", ft_memchr(s, 'w', 7));
	printf("original: %s\n", memchr(s, 'w', 7));
}
 */