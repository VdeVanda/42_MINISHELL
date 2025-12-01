/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 12:59:15 by vabatist          #+#    #+#             */
/*   Updated: 2024/11/16 11:21:03 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
memcomp: string.h
memcomp compares the first n bytes of two memory blocks.
Returns an integer less than, equal to, or greater than zero
if the first num bytes of ptr1 are found to be less than, match,
or be greater than the first num bytes of ptr2.
*/
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*temp_s1;
	const unsigned char	*temp_s2;
	size_t				i;

	temp_s1 = (const unsigned char *)s1;
	temp_s2 = (const unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if (temp_s1[i] != temp_s2[i])
			return (temp_s1[i] - temp_s2[i]);
		i++;
	}
	return (0);
}
/* int	main(void)
{
	const char	s1[] = "hello";
	const char	s2[] = "hell";

	printf("my ft: %d\n", ft_memcmp(s1, s2, 5));
	printf("original: %d\n", memcmp(s1, s2, 5));
} */