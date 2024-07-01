#include "../include/so_long.h"

static char	*read_line(int fd, char *leftover)
{
	char	buffer[BUFFER_SIZE + 1];
	int		bytes_read;
	char	*newline;

	while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[bytes_read] = '\0';
		leftover = ft_strjoin(leftover, buffer);
		if ((newline = ft_strchr(leftover, '\n')))
			return (leftover);
	}
	return (leftover);
}

int	get_next_line(int fd, char **line)
{
	static char	*leftover;
	char		*newline;
	char		*temp;

	if (!leftover)
		leftover = ft_strdup("");
	if (!line || fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (-1);
	leftover = read_line(fd, leftover);
	if (!leftover)
		return (-1);
	if ((newline = ft_strchr(leftover, '\n')))
	{
		*newline = '\0';
		*line = ft_strdup(leftover);
		temp = ft_strdup(newline + 1);
		free(leftover);
		leftover = temp;
		return (1);
	}
	*line = ft_strdup(leftover);
	free(leftover);
	leftover = NULL;
	return (0);
}
