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
	int		width;
	int		height;

	if (argc != 2)
	{
		printf("Usage: %s <map.ber>\n", argv[0]);
		return (1);
	}

	get_map_size(argv[1], &width, &height);

	game.mlx = mlx_init();
	if (!game.mlx)
		error_exit("Failed to initialize mlx");

	game.win = mlx_new_window(game.mlx, width * 100, height * 100, "Nom du jeu");
	if (!game.win)
		error_exit("Failed to create window");

	display_map(&game, argv[1]);

	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_loop(game.mlx);

	return (0);
}
