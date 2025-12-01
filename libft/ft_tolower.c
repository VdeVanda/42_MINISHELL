/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:52:20 by vabatist          #+#    #+#             */
/*   Updated: 2024/11/13 09:02:11 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	tolower: <ctype.h>
	Converts a character to lowercase if it is uppercase.
    If c is not an uppercase letter, it returns c unchanged.
*/
int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}
/* int	main(void)
{
	printf("%c\n", ft_tolower('V'));
	printf("%c\n", tolower('V'));
	return (0);
} */
