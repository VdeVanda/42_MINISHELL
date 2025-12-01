/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 09:30:35 by vabatist          #+#    #+#             */
/*   Updated: 2024/11/23 09:43:58 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
ft_split allocates (with malloc(3)) and returns an array
of strings obtained by splitting ’s’ using the
character ’c’ as a delimiter. The array must end
with a NULL pointer.
Parameters
s: The string to be split.
c: The delimiter character.
Return value: The array of new strings resulting from the split.
NULL if the allocation fails.
*/
static int	ft_wordcount(char const *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			i++;
			while (*s && *s != c)
				s++;
		}
	}
	return (i);
}

static size_t	ft_word_size(const char *str, int n, char c)
{
	size_t	i;

	i = 0;
	while (str[n] && str[n] != c)
	{
		n++;
		i++;
	}
	return (i);
}

char	**ft_split(char const *s, char c)
{
	int		size;
	int		a;
	int		i;
	char	**r;

	i = 0;
	a = 0;
	size = ft_wordcount(s, c);
	r = (char **)malloc(sizeof(char *) * (size + 1));
	if (r == 0)
		return (NULL);
	r[size] = NULL;
	while (a < size)
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			r[a] = ft_substr(s, i, ft_word_size(s, i, c));
		while (s[i] && s[i] != c)
			i++;
		a++;
	}
	return (r);
}

/*
int	main(void)
{

	// Word . word . word
	char str[] = "apple.berry.orange";
	char **result;

	result = ft_split(str, '.');
	printf("Result[0]: %s\n", result[0]);
	printf("Result[1]: %s\n", result[1]);
	printf("Result[2]: %s\n", result[2]);

	for (int i = 0; result[i] != NULL; i++)
	{
		free(result[i]);
	}
	free(result);
} */