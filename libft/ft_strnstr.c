/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 15:12:40 by vabatist          #+#    #+#             */
/*   Updated: 2024/11/13 10:16:50 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
strnstr: doenst exist in the original library.
strnstr is used to locate a substring in a string in len bytes.
Returns the string from the point where it found.
*/
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str_big;
	char	*str_little;

	i = 0;
	str_big = (char *)haystack;
	str_little = (char *)needle;
	if (!*needle)
		return (str_big);
	while (str_big[i] && i < len)
	{
		j = 0;
		while ((str_big[i + j] == str_little[j]) && i + j < len && needle[j])
			j++;
		if (j >= ft_strlen(str_little))
			return (str_big + i);
		i++;
	}
	return (NULL);
}

/* #include <bsd/string.h>
original function compiles only on terminal with 
cc -lbsd ft_strnstr.c ft_strlen.c
int	main(void)
{
	char	big[] = "Vanda Batista Oliveira";
	char	little[] = "Batista";

	printf("my little string: %s\n", ft_strnstr(big, little, 20));
	printf("Original: %s\n", strnstr(big, little, 20));
    return (0);
} */