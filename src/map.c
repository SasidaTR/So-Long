#include "../include/so_long.h"

void	put_image_to_window(t_gmc *gmc, int x, int y)
{
	if (gmc->map->map[y][x] == '0')
		mlx_put_image_to_window(gmc->game->mlx, gmc->game->win, gmc->map->zero,
			x * gmc->map->design->img_width, y * gmc->map->design->img_height);
	else if (gmc->map->map[y][x] == '1')
		mlx_put_image_to_window(gmc->game->mlx, gmc->game->win, gmc->map->one,
			x * gmc->map->design->img_width, y * gmc->map->design->img_height);
	else if (gmc->map->map[y][x] == 'C')
		mlx_put_image_to_window(gmc->game->mlx, gmc->game->win, gmc->map->c,
			x * gmc->map->design->img_width, y * gmc->map->design->img_height);
	else if (gmc->map->map[y][x] == 'E')
		mlx_put_image_to_window(gmc->game->mlx, gmc->game->win, gmc->map->e,
			x * gmc->map->design->img_width, y * gmc->map->design->img_height);
	else if (gmc->map->map[y][x] == 'M')
		mlx_put_image_to_window(gmc->game->mlx, gmc->game->win,
			gmc->map->design->m_imgs[gmc->map->design->current_monster_img],
			x * gmc->map->design->img_width, y * gmc->map->design->img_height);
	else if (gmc->map->map[y][x] == 'P')
	{
		mlx_put_image_to_window(gmc->game->mlx, gmc->game->win,
			gmc->map->design->current_player_img,
			x * gmc->map->design->img_width,
			y * gmc->map->design->img_height);
		gmc->game->player_x = x;
		gmc->game->player_y = y;
	}
}

void	display_map(t_gmc *gmc)
{
	int	y;
	int	x;

	y = 0;
	while (gmc->map->map[y])
	{
		x = 0;
		while (gmc->map->map[y][x])
		{
			put_image_to_window(gmc, x, y);
			x++;
		}
		y++;
	}
}

void	find_player_position(t_gmc *gmc)
{
	int	y;
	int	x;

	y = 0;
	while (gmc->map->map[y])
	{
		x = 0;
		while (gmc->map->map[y][x])
		{
			if (gmc->map->map[y][x] == 'P')
			{
				gmc->game->player_x = x;
				gmc->game->player_y = y;
				return ;
			}
			x++;
		}
		y++;
	}
	error_exit(gmc, "Player position not found");
}

void	read_map_line(t_gmc *gmc, int fd, int *line_count)
{
	char	*line;
	char	**temp;

	while (get_next_line(fd, &line) > 0)
	{
		temp = realloc(gmc->map->map, sizeof(char *) * (*line_count + 2));
		if (!temp)
		{
			free(line);
			error_exit(gmc, "Failed to reallocate memory for map content");
		}
		gmc->map->map = temp;
		gmc->map->map[*line_count] = ft_strdup(line);
		if (!gmc->map->map[*line_count])
		{
			free(line);
			error_exit(gmc, "Failed to allocate memory for map content line");
		}
		free(line);
		(*line_count)++;
	}
}

void	get_map_size(t_gmc *gmc)
{
	int		fd;
	int		line_count;

	fd = open(gmc->map->map_file, O_RDONLY);
	if (fd < 0)
		error_exit(gmc, "Failed to open map file");
	gmc->map->map = NULL;
	line_count = 0;
	read_map_line(gmc, fd, &line_count);
	if (line_count > 0)
		gmc->map->map[line_count] = NULL;
	close(fd);
}
