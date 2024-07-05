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
				mlx_put_image_to_window(game->mlx, game->win, map->zero, x * map->design->img_width, y * map->design->img_height);
			else if (map->map[y][x] == '1')
				mlx_put_image_to_window(game->mlx, game->win, map->one, x * map->design->img_width, y * map->design->img_height);
			else if (map->map[y][x] == 'C')
				mlx_put_image_to_window(game->mlx, game->win, map->c, x * map->design->img_width, y * map->design->img_height);
			else if (map->map[y][x] == 'E')
				mlx_put_image_to_window(game->mlx, game->win, map->e, x * map->design->img_width, y * map->design->img_height);
			else if (map->map[y][x] == 'P')
			{
				mlx_put_image_to_window(game->mlx, game->win, map->p, x * map->design->img_width, y * map->design->img_height);
				game->player_x = x;
				game->player_y = y;
			}
			x++;
		}
		y++;
	}
}

int count_collectables(t_map *map)
{
	int y, x, count = 0;
	for (y = 0; map->map[y]; y++)
	{
		for (x = 0; map->map[y][x]; x++)
		{
			if (map->map[y][x] == 'C')
				count++;
		}
	}
	return count;
}

void	get_map_size(char *file, int *width, int *height, t_map *map)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_exit("Failed to open map file");
	map->map = malloc(sizeof(char *) * (*height));
	if (!map->map)
		error_exit("Failed to allocate memory for map content");
	i = 0;
	*width = 0;
	*height = 0;
	while (get_next_line(fd, &line) > 0)
	{
		map->map[i] = ft_strdup(line);
		if (!map->map[i])
			error_exit("Failed to allocate memory for map content line");
		*width = ft_strlen(line);
		(*height)++;
		free(line);
		i++;
	}
	close(fd);
}
