/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:20:09 by vabatist          #+#    #+#             */
/*   Updated: 2024/11/16 11:18:45 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
isdigit: ctype.h
isdigit checks if a character is a digit (0-9).
*/
int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
/* 
# include <stdio.h>

int	main(void)
{
	printf("%d\n",ft_isdigit('1'));
	return(0);
} */
