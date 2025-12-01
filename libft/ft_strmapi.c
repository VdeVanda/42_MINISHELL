/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 09:45:45 by vabatist          #+#    #+#             */
/*   Updated: 2024/11/23 09:46:08 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
strmapi applies the function f to each character of the
string s, passing its index as the first argument
and the character itself as the second. A new
string is created (using malloc(3)) to collect the
results from the successive applications of f.
Parameters: s: The string on which to iterate.
f: The function to apply to each character.
Returns: The string created from the successive applications
of ’f’.
Returns NULL if the allocation fails.
*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*str;

	if (!s)
		return (NULL);
	i = 0;
	str = malloc((ft_strlen(s)) + 1 * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}

/*
char	ft_toupper_two(unsigned int i, char c)
{
	(void)i;
	return (char)toupper((int)c);
}

int	main(void)
{
	char	*str;
	char	*new_str;

	str = "Hello";
	new_str = ft_strmapi(str, ft_toupper_two);
	printf("%s\n", new_str);
	free(new_str);
	return (0);
}
*/