/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 11:34:39 by vabatist          #+#    #+#             */
/*   Updated: 2024/11/23 16:38:01 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
strncmp: string.h
strcmp compares the first n characters of str1 and str2
Returns an integer less than, equal to, or greater than zero
if the first n characters of s1 are found, respectively, to be less than,
to match, or be greater than the first n characters of str2.
*/
int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((str1[i] || str2[i]) && i < n)
	{
		if (str1[i] != str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	printf("Mine: %d\n", ft_strncmp("vanda", "vandinha", 4));
	printf("Original: %d\n", strncmp("vanda", "vandinha", 4));
	printf("Mine: %d\n", ft_strncmp("vanda", "vandinha", 7));
	printf("Original: %d\n", strncmp("vanda", "vandinha", 7));
	printf("Mine: %d\n", ft_strncmp("vandinha", "van", 4));
	printf("Original: %d\n", strncmp("vandinha", "van", 4));
} */