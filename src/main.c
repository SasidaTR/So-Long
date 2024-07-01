#include "../include/so_long.h"

void	error_exit(char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

int	close_window(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
	return (0);
}

void	display_map(t_game *game)
{
	int		x, y;
	char	*line;
	int		fd = open(game->map_file, O_RDONLY);

	if (fd < 0)
		error_exit("Failed to open map file");

	y = 0;
	while (get_next_line(fd, &line) > 0)
	{
		x = 0;
		while (line[x])
		{
			if (line[x] == '0')
				mlx_put_image_to_window(game->mlx, game->win, game->img1, x * 32, y * 32);
			else if (line[x] == '1')
				mlx_put_image_to_window(game->mlx, game->win, game->img2, x * 32, y * 32);
			x++;
		}
		free(line);
		y++;
	}
	close(fd);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		printf("Usage: %s <map.ber>\n", argv[0]);
		return (1);
	}

	game.map_file = argv[1];
	game.mlx = mlx_init();
	if (!game.mlx)
		error_exit("Failed to initialize mlx");

	game.win = mlx_new_window(game.mlx, 800, 600, "Nom du jeu");
	if (!game.win)
		error_exit("Failed to create window");

	game.img1 = mlx_xpm_file_to_image(game.mlx, "graphics/img1.xpm", &game.img_width, &game.img_height);
	if (!game.img1)
		error_exit("Failed to load image 1");

	game.img2 = mlx_xpm_file_to_image(game.mlx, "graphics/img2.xpm", &game.img_width, &game.img_height);
	if (!game.img2)
		error_exit("Failed to load image 2");

	display_map(&game);

	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_loop(game.mlx);

	return (0);
}
