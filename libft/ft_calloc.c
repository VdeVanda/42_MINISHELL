/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:43:17 by vabatist          #+#    #+#             */
/*   Updated: 2024/11/23 10:25:22 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
calloc: stdlib.h
calloc function allocates memory for an array of nmemb elements
of size bytes each and returns a pointer to the allocated memory.
The memory is set to zero.
*/
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*result;
	size_t	total_mem;

	total_mem = nmemb * size;
	if (total_mem && (total_mem / size) != nmemb)
		return (NULL);
	result = malloc(total_mem);
	if (result)
		ft_bzero(result, total_mem);
	return (result);
}
/* int main(void)
{
	char *str1;
	char *str2;
	int i = 0;
	str1 = ft_calloc(10, sizeof(char));
	str2 = calloc(10, sizeof(char));
	while(i < 10)
	{
		printf("str1[%d]: %c\n", i, str1[i]);
		printf("str2[%d]: %c\n", i, str2[i]);
		if (str1[i] != str2[i])
			printf("KO\n");
		else
			printf("OK\n");
		i++;
	}
	free(str1);
	free(str2);
	return (0);
} */