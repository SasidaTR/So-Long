#include "../include/so_long.h"

void	display_map(t_game *game)
{
	int		x;
	int		y;
	char	*line;
	int		fd;
	
	fd = open(game->map_file, O_RDONLY);
	if (fd < 0)
		error_exit("Failed to open map file");
	y = 0;
	while (get_next_line(fd, &line) > 0)
	{
		x = 0;
		while (line[x])
		{
			if (line[x] == '0')
				mlx_put_image_to_window(game->mlx, game->win, game->zero, x * game->img_width, y * game->img_height);
			else if (line[x] == '1')
				mlx_put_image_to_window(game->mlx, game->win, game->one, x * game->img_width, y * game->img_height);
			else if (line[x] == 'C')
				mlx_put_image_to_window(game->mlx, game->win, game->one, x * game->img_width, y * game->img_height);
			else if (line[x] == 'E')
				mlx_put_image_to_window(game->mlx, game->win, game->one, x * game->img_width, y * game->img_height);
			else if (line[x] == 'P')
				mlx_put_image_to_window(game->mlx, game->win, game->one, x * game->img_width, y * game->img_height);
			x++;
		}
		free(line);
		y++;
	}
	close(fd);
}
