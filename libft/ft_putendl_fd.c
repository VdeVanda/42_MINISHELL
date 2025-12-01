/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 09:06:15 by vabatist          #+#    #+#             */
/*   Updated: 2024/11/20 09:28:08 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
putendl_fd outputs the string ’s’ to the given file descriptor
followed by a newline.
Parameters:
s: The string to output.
fd: The file descriptor on which to write.
*/
void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}
/* int main(void)
{
	int fd = open("Name.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

	ft_putendl_fd("Vanda Oliveira", fd);
	close(fd);
} */