/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 10:04:12 by vabatist          #+#    #+#             */
/*   Updated: 2024/11/09 13:19:52 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
strlcat: string.h
strlcat appends the source string to the destination string,
but only up to a specified size to prevent buffer overflow.
returns the total length of the string it tried to create, that is,
the initial length of dst plus the length of src.
*/
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_dst;
	size_t	len_src;
	size_t	i;

	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	if (size <= len_dst)
		return (size + len_src);
	i = 0;
	while (src[i] && i < size - len_dst - 1)
	{
		dst[len_dst + i] = src[i];
		i++;
	}
	dst[len_dst + i] = '\0';
	return (len_dst + len_src);
}
/*
int	main(void)
{
	char dst[15] = "Hello, ";
	const char *src = "World!";
	size_t size = sizeof(dst);

	printf("dst antes: %s\n", dst);
	// ft_strlcat(dst, src, 15);
	strlcat(dst, src, size);
	printf("dst depois: %s\n", dst);

	return (0);
} */