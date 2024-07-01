#include "../include/so_long.h"

void	error_exit(char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

char	**read_map(const char *filename, int *width, int *height)
{
	int		fd;
	char	buffer[1024];
	int		bytes_read;
	char	**map;
	int		i;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit("Failed to open file");
	bytes_read = read(fd, buffer, 1024);
	if (bytes_read <= 0)
		error_exit("Failed to read file");
	buffer[bytes_read] = '\0';
	close(fd);

	// Count width and height
	*width = 0;
	*height = 1;
	for (i = 0; buffer[i]; i++) {
		if (buffer[i] == '\n')
			(*height)++;
		if (*height == 1)
			(*width)++;
	}

	// Allocate memory for the map
	map = (char **)malloc(*height * sizeof(char *));
	if (!map)
		error_exit("Failed to allocate memory for map");

	// Fill the map
	int row = 0;
	map[row++] = buffer;
	for (i = 0; buffer[i]; i++) {
		if (buffer[i] == '\n') {
			buffer[i] = '\0';
			if (row < *height)
				map[row++] = buffer + i + 1;
		}
	}

	return map;
}

void	draw_map(t_game *game)
{
	for (int y = 0; y < game->map_height; y++) {
		for (int x = 0; x < game->map_width; x++) {
			void *img = (game->map[y][x] == '1') ? game->img1 : game->img2;
			mlx_put_image_to_window(game->mlx, game->win, img, x * game->img_width, y * game->img_height);
		}
	}
}

int	close_window(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		printf("Usage: %s <map.ber>\n", argv[0]);
		return (1);
	}

	game.mlx = mlx_init();
	if (!game.mlx)
		error_exit("Failed to initialize mlx");

	game.win = mlx_new_window(game.mlx, 800, 600, "Nom du jeu");
	if (!game.win)
		error_exit("Failed to create window");

	game.map = read_map(argv[1], &game.map_width, &game.map_height);
	game.img1 = mlx_xpm_file_to_image(game.mlx, "./graphics/img1.xpm", &game.img_width, &game.img_height);
	if (!game.img1)
		error_exit("Failed to load img1.xpm");

	game.img2 = mlx_xpm_file_to_image(game.mlx, "./graphics/img2.xpm", &game.img_width, &game.img_height);
	if (!game.img2)
		error_exit("Failed to load img2.xpm");

	draw_map(&game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_loop(game.mlx);

	return (0);
}
