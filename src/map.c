#include "../include/so_long.h"

void	get_map_size(char *file, int *width, int *height)
{
	int		fd;
	char	*line;
	int		len;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_exit("Failed to open map file");
	*width = 0;
	*height = 0;
	while (get_next_line(fd, &line) > 0)
	{
		len = ft_strlen(line);
		if (len > *width)
			*width = len;
		(*height)++;
		free(line);
	}
	close(fd);
}

void	display_map(t_game *game, t_map *map)
{
	int		x;
	int		y;
	char	*line;
	int		fd;

	fd = open(map->map_file, O_RDONLY);
	if (fd < 0)
		error_exit("Failed to open map file");
	y = 0;
	while (get_next_line(fd, &line) > 0)
	{
		x = 0;
		while (line[x])
		{
			if (line[x] == '0')
				mlx_put_image_to_window(game->mlx, game->win, map->zero, x * map->design->img_width, y * map->design->img_height);
			else if (line[x] == '1')
				mlx_put_image_to_window(game->mlx, game->win, map->one, x * map->design->img_width, y * map->design->img_height);
			else if (line[x] == 'C')
				mlx_put_image_to_window(game->mlx, game->win, map->c, x * map->design->img_width, y * map->design->img_height);
			else if (line[x] == 'E')
				mlx_put_image_to_window(game->mlx, game->win, map->e, x * map->design->img_width, y * map->design->img_height);
			else if (line[x] == 'P')
			{
				mlx_put_image_to_window(game->mlx, game->win, map->p, x * map->design->img_width, y * map->design->img_height);
				game->player_x = x;
				game->player_y = y;
			}
			x++;
		}
		free(line);
		y++;
	}
	close(fd);
}

void	redraw_map(t_game *game, t_map *map)
{
	display_map(game, map);
	mlx_put_image_to_window(game->mlx, game->win, map->p, game->player_x * map->design->img_width, game->player_y * map->design->img_height);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == 65307)
		close_window(game);
	else if (keycode == 119)
		game->player_y--;
	else if (keycode == 115)
		game->player_y++;
	else if (keycode == 97)
		game->player_x--;
	else if (keycode == 100)
		game->player_x++;
	redraw_map(game, game->map);
	return (0);
}
