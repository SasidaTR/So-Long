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

void	display_map(t_game *game, t_map *map)
{
	int		y;
	int		x;

	y = 0;
	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x])
		{
			if (map->map[y][x] == '0')
				mlx_put_image_to_window(game->mlx, game->win, map->zero,
					x * map->design->img_width, y * map->design->img_height);
			else if (map->map[y][x] == '1')
				mlx_put_image_to_window(game->mlx, game->win, map->one,
					x * map->design->img_width, y * map->design->img_height);
			else if (map->map[y][x] == 'C')
				mlx_put_image_to_window(game->mlx, game->win, map->c,
					x * map->design->img_width, y * map->design->img_height);
			else if (map->map[y][x] == 'E')
				mlx_put_image_to_window(game->mlx, game->win, map->e,
					x * map->design->img_width, y * map->design->img_height);
			else if (map->map[y][x] == 'P')
			{
				mlx_put_image_to_window(game->mlx, game->win, map->p,
					x * map->design->img_width, y * map->design->img_height);
				game->player_x = x;
				game->player_y = y;
			}
			x++;
		}
		y++;
	}
}

int	count_collectables(t_map *map)
{
	int	y;
	int	x;
	int	count;

	y = 0;
	count = 0;
	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x])
		{
			if (map->map[y][x] == 'C')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

void	get_map_size(char *file, int *width, int *height, t_map *map)
{
	int		fd;
	char	*line;
	int		i;
	int		line_count;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_exit("Failed to open map file");
	line_count = 0;
	while (get_next_line(fd, &line) > 0)
	{
		line_count++;
		free(line);
	}
	close(fd);
	*height = line_count;
	map->map = malloc(sizeof(char *) * (*height + 1));
	if (!map->map)
		error_exit("Failed to allocate memory for map content");
	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_exit("Failed to open map file");
	i = 0;
	while (get_next_line(fd, &line) > 0)
	{
		map->map[i] = ft_strdup(line);
		if (!map->map[i])
			error_exit("Failed to allocate memory for map content line");
		if (i == 0)
			*width = ft_strlen(line);
		free(line);
		i++;
	}
	map->map[i] = NULL;
	close(fd);
}
