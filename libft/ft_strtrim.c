/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:32:28 by vabatist          #+#    #+#             */
/*   Updated: 2024/11/20 20:17:11 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
ft_strtrim allocates (with malloc(3)) and returns a copy of ’s1’
with the characters specified in ’set’ removed from the beginning
and the end of the string
Parameters:
s1: The string to be trimmed.
set: The reference set of characters to trim.
*/
char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;

	end = ft_strlen(s1) - 1;
	start = 0;
	if (s1 == 0)
		return (NULL);
	if (*set == '\0')
		return (ft_strdup(s1));
	while (s1[start] && (ft_strchr(set, s1[start])))
		start++;
	while (s1[end] && (ft_strchr(set, s1[end])))
		end--;
	return (ft_substr(s1, start, end - start + 1));
}

/* int main(void)
{
	char *s1 = "   hello, world!   ";
	char *set = " ";
	char *new_str = ft_strtrim(s1, set);
	printf("new_str: %s\n", new_str);
	free(new_str);
	return (0);
} */
