/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 10:13:44 by vabatist          #+#    #+#             */
/*   Updated: 2024/11/16 11:09:11 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
putchar_fd is defined to write a given character (char c)
to a specified file descriptor (int fd).
*/
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
/* int	main(void)
{
	int fd = open("V.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    ft_putchar_fd('v', fd);
	close(fd);
} */
