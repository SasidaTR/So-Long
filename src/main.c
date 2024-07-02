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
	game.zero = mlx_xpm_file_to_image(game.mlx, "graphics/0.xpm", &game.img_width, &game.img_height);
	if (!game.zero)
		error_exit("Failed to load the 0s");
	game.one = mlx_xpm_file_to_image(game.mlx, "graphics/1.xpm", &game.img_width, &game.img_height);
	if (!game.one)
		error_exit("Failed to load the 1s");
	display_map(&game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_loop(game.mlx);
	return (0);
}
