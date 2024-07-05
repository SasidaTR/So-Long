/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trischma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:11:31 by trischma          #+#    #+#             */
/*   Updated: 2024/07/05 15:11:35 by trischma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static char	*read_line(int fd, char *leftover)
{
	char	buffer[BUFFER_SIZE + 1];
	int		bytes_read;
	char	*newline;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		leftover = ft_strjoin(leftover, buffer);
		newline = ft_strchr(leftover, '\n');
		if (newline)
			return (leftover);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	return (leftover);
}

static int	handle_newline(char **line, char **leftover)
{
	char	*newline;
	char	*temp;

	newline = ft_strchr(*leftover, '\n');
	if (newline)
	{
		*newline = '\0';
		*line = ft_strdup(*leftover);
		temp = ft_strdup(newline + 1);
		free(*leftover);
		*leftover = temp;
		return (1);
	}
	return (0);
}

static int	handle_eof(char **line, char **leftover)
{
	if (**leftover)
	{
		*line = ft_strdup(*leftover);
		free(*leftover);
		*leftover = NULL;
		return (1);
	}
	free(*leftover);
	*leftover = NULL;
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char	*leftover;

	if (!leftover)
		leftover = ft_strdup("");
	if (!line || fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (-1);
	leftover = read_line(fd, leftover);
	if (!leftover)
		return (-1);
	if (handle_newline(line, &leftover))
		return (1);
	return (handle_eof(line, &leftover));
}
