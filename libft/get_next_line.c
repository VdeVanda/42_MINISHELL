/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 11:32:40 by vabatist          #+#    #+#             */
/*   Updated: 2025/03/19 14:42:27 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	char		*line;
	static char	buffer[BUFFER_SIZE + 1];
	int			i;

	i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		while (buffer[i])
			buffer[i++] = 0;
		return (NULL);
	}
	line = NULL;
	while (*buffer || read(fd, buffer, BUFFER_SIZE) > 0)
	{
		line = ft_strjoin_gnl(line, buffer);
		if (newline(buffer) == 1)
			break ;
	}
	return (line);
}

/* int	main(void)
{
	int		fd;
	char	*line;

	fd = open("text.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	printf("\nBUFFER SIZE: %i\n", BUFFER_SIZE);
	close(fd);
	return (0);
} */
