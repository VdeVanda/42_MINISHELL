/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 11:33:08 by vabatist          #+#    #+#             */
/*   Updated: 2024/11/16 11:40:04 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
putstring_fd is defined to write a given string (char *s)
on a specified file descriptor (int fd).
*/
void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}
/* int	main(void)
{
	int fd = open("Name.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

	ft_putstr_fd("Vanda Oliveira", fd);
	close(fd);
} */