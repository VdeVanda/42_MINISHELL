/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 09:44:39 by vabatist          #+#    #+#             */
/*   Updated: 2024/11/23 09:44:56 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
ft_striteri applies the function f to each character of the
string passed as argument, passing its index
as first argument. Each character is passed by
address to ’f’ to be modified if necessary.
Parameters:
s: The string on which to iterate.
f: The function to apply to each character.
Return value: None.
*/
void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

/*
void	ft_toupper_two(unsigned int i, char *c)
{
	(void)i;
	*c = (char)toupper((int)*c);
}

int	main(void)
{
	char	str[] = "hello, WORLD!";

	ft_striteri(str, ft_toupper_two);
	printf("%s\n", str);
	return (0);
}
 */