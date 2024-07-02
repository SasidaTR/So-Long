#include "../include/so_long.h"

void	get_map_size(char *file, int *width, int *height)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_exit("Failed to open map file");

	*width = 0;
	*height = 0;
	while (get_next_line(fd, &line) > 0)
	{
		int len = ft_strlen(line);
		if (len > *width)
			*width = len;
		(*height)++;
		free(line);
	}
	close(fd);
}

void display_map(t_game *game, char *argv)
{
    t_map map;
    int x;
    int y;
    char *line;
    int fd;

    map.map_file = argv;
    map.design = malloc(sizeof(t_design));
    if (!map.design)
        error_exit("Failed to allocate memory for map design");
    map.zero = mlx_xpm_file_to_image(game->mlx, "graphics/0.xpm", &map.design->img_width, &map.design->img_height);
    if (!map.zero)
        error_exit("Failed to load the 0s");
    map.one = mlx_xpm_file_to_image(game->mlx, "graphics/1.xpm", &map.design->img_width, &map.design->img_height);
    if (!map.one)
        error_exit("Failed to load the 1s");
    map.c = mlx_xpm_file_to_image(game->mlx, "graphics/c.xpm", &map.design->img_width, &map.design->img_height);
    if (!map.c)
        error_exit("Failed to load the Cs");
    map.e = mlx_xpm_file_to_image(game->mlx, "graphics/e.xpm", &map.design->img_width, &map.design->img_height);
    if (!map.e)
        error_exit("Failed to load the E");
    map.p = mlx_xpm_file_to_image(game->mlx, "graphics/p.xpm", &map.design->img_width, &map.design->img_height);
    if (!map.p)
        error_exit("Failed to load the P");
    fd = open(map.map_file, O_RDONLY);
    if (fd < 0)
        error_exit("Failed to open map file");
    y = 0;
    while (get_next_line(fd, &line) > 0)
    {
        x = 0;
        while (line[x])
        {
            if (line[x] == '0')
                mlx_put_image_to_window(game->mlx, game->win, map.zero, x * map.design->img_width, y * map.design->img_height);
            else if (line[x] == '1')
                mlx_put_image_to_window(game->mlx, game->win, map.one, x * map.design->img_width, y * map.design->img_height);
            else if (line[x] == 'C')
                mlx_put_image_to_window(game->mlx, game->win, map.c, x * map.design->img_width, y * map.design->img_height);
            else if (line[x] == 'E')
                mlx_put_image_to_window(game->mlx, game->win, map.e, x * map.design->img_width, y * map.design->img_height);
            else if (line[x] == 'P')
                mlx_put_image_to_window(game->mlx, game->win, map.p, x * map.design->img_width, y * map.design->img_height);
            x++;
        }
        free(line);
        y++;
    }
    close(fd);
    free(map.design);
}
