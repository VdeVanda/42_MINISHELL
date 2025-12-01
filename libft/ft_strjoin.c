/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:35:56 by vabatist          #+#    #+#             */
/*   Updated: 2024/11/20 14:28:10 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
ft_strjoin allocates (with malloc(3)) and returns a new string,
which is the result of the concatenation of ’s1’ and ’s2’.
NULL if the allocation fails
Parameters:
s1: The prefix string.
s2: The suffix string.
*/
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	i = 0;
	j = 0;
	new_str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	while (s1[i])
		new_str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		new_str[j++] = s2[i++];
	new_str[j] = '\0';
	return (new_str);
}
/* int main(void)
{
	char *s1 = "hello, ";
	char *s2 = "world!";
	char *new_str = ft_strjoin(s1, s2);
	printf("new_str: %s\n", new_str);
	free(new_str);
	return (0);
} */