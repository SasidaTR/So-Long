/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trischma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:41:46 by trischma          #+#    #+#             */
/*   Updated: 2024/07/11 15:41:47 by trischma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static char	*read_until_newline(int fd, char *buffer)
{
	char	*line;
	char	*newline;
	int		countread;

	line = ft_strdup(buffer);
	newline = ft_strchr(line, '\n');
	while (!newline)
	{
		countread = read(fd, buffer, BUFFER_SIZE);
		if (countread <= 0)
			break ;
		buffer[countread] = '\0';
		line = ft_strjoin(line, buffer);
		newline = ft_strchr(line, '\n');
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*line;
	char		*newline;
	int			to_copy;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	line = read_until_newline(fd, buf);
	if (!line || ft_strlen(line) == 0)
		return (free(line), NULL);
	newline = ft_strchr(line, '\n');
	if (newline != NULL)
	{
		to_copy = newline - line;
		ft_strcpy(buf, newline + 1);
		line[to_copy] = '\0';
	}
	else
	{
		to_copy = ft_strlen(line);
		buf[0] = '\0';
	}
	return (line);
}
