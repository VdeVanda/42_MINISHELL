/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 11:33:47 by vabatist          #+#    #+#             */
/*   Updated: 2025/03/19 14:42:20 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_gnl(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	return (i);
}

char	*ft_strjoin_gnl(char *line, char *buffer)
{
	char	*newstr;
	size_t	i;

	newstr = malloc(ft_strlen_gnl(line) + ft_strlen_gnl(buffer) + 1);
	if (!newstr)
		return (NULL);
	i = 0;
	while (line && line[i])
	{
		newstr[i] = line[i];
		i++;
	}
	free(line);
	while (*buffer)
	{
		newstr[i++] = *buffer;
		if (*buffer++ == '\n')
			break ;
	}
	newstr[i] = 0;
	return (newstr);
}

int	newline(char *buffer)
{
	int	i;
	int	afternewline;
	int	findnewline;

	i = 0;
	afternewline = 0;
	findnewline = 0;
	while (buffer[i])
	{
		if (findnewline == 1)
			buffer[afternewline++] = buffer[i];
		if (buffer[i] == '\n')
			findnewline = 1;
		buffer[i++] = 0;
	}
	return (findnewline);
}
