/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:18:12 by vabatist          #+#    #+#             */
/*   Updated: 2025/02/01 12:55:54 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
strdup: <string.h>
returns a pointer to a new string which is a duplicate of the string s.
Memory for the new string  is  obtained  with malloc,
and can be freed with free.
*/
char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*dup;

	len = ft_strlen(s);
	dup = ft_calloc(len + 1, sizeof(char));
	if (dup)
		ft_strlcpy(dup, s, len + 1);
	return (dup);
}
/* int main(void)
{
	char *str = "hello";
	char *dup1 = ft_strdup(str);
	char *dup2 = strdup(str);
	if(dup1 && dup2 && ft_strncmp(dup1, dup2, ft_strlen(str)) == 0)
		printf("Both strings are equal\n");
	else
		printf("Strings are different\n");
	printf("dup1: %s\n", dup1);
	printf("dup2: %s\n", dup2);
	free(dup1);
	free(dup2);
	return (0);
} */