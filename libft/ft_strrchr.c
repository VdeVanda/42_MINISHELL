/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 11:19:39 by vabatist          #+#    #+#             */
/*   Updated: 2025/02/01 12:57:30 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
strrchr: string.h
strrchr is used to locate the last occurrence of a character in a string.
Returns a pointer to that last occurrence of the character in the string.
Therefore, it effectively returns one character and all characters
following it in the string.
*/
char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}

/* char	*result;
	result = NULL;
	while (*s)
	{
		if (*s == (char)c)
			result = (char *)s;
		s++;
	}
	if (result != NULL)
		return (result);
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL); */

/* int	main(void)
{
	const char	s[] = "hello, world!";
	char		*result;

	//const char	*t;
	printf("my_ft: %s\n", ft_strrchr(s, 0));
	//printf("original: %s\n", strrchr(s, 0));
	//printf("original: %s\n", strrchr(t, 'o'));
	return (0);
} */
/* #include <stdio.h>
#include <string.h>
char	*ft_strrchr(const char *s, int c);
void	test_ft_strrchr(void) {
	// Test 1: Empty String
	s = "";
	result = ft_strrchr(s, 'a');
	printf("Test 1 (Empty String): %s\n", result == NULL ? "NULL" : result);
	// Test 2: Character Not Present
	s = "Hello, World!";
	result = ft_strrchr(s, 'z');
	printf("Test 2 (Character Not Present): %s\n",
		result == NULL ? "NULL" : result);
	// Test 3: Character at Beginning
	s = "abcde";
	result = ft_strrchr(s, 'a');
	printf("Test 3 (Character at Beginning): %s\n",
		result == NULL ? "NULL" : result);
	// Test 4: Character at End
	s = "abcde";
	result = ft_strrchr(s, 'e');
	printf("Test 4 (Character at End): %s\n", result == NULL ? "NULL" : result);
	// Test 5: Multiple Occurrences
	s = "abacad";
	result = ft_strrchr(s, 'a');
	printf("Test 5 (Multiple Occurrences): %s\n",
		result == NULL ? "NULL" : result);
	// Test 6: Null Input
	s = NULL;
	result = ft_strrchr(s, 'a');
	printf("Test 6 (Null Input): %s\n", result == NULL ? "NULL" : result);
}

int	main(void) {
	test_ft_strrchr();
	return (0);
} */