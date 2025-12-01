/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:35:53 by vabatist          #+#    #+#             */
/*   Updated: 2024/11/13 09:02:04 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
toupper: <ctype.h>
Converts a character to lowercase if it is uppercase.
If c is not an uppercase letter, it returns c unchanged.
*/
int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}
/* int	main(void)
{
	printf("%c\n", ft_toupper('v'));
	printf("%c\n", toupper('v'));
	return (0);
} */