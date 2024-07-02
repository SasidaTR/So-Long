#include "../include/so_long.h"

void	error_exit(char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

int	close_window(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;
	t_map	map;
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
	map.map_file = argv[1];
	map.design = malloc(sizeof(t_design));
	if (!map.design)
		error_exit("Failed to allocate memory for map design");
	map.zero = mlx_xpm_file_to_image(game.mlx, "graphics/0.xpm", &map.design->img_width, &map.design->img_height);
	if (!map.zero)
		error_exit("Failed to load the 0s");
	map.one = mlx_xpm_file_to_image(game.mlx, "graphics/1.xpm", &map.design->img_width, &map.design->img_height);
	if (!map.one)
		error_exit("Failed to load the 1s");
	map.c = mlx_xpm_file_to_image(game.mlx, "graphics/c.xpm", &map.design->img_width, &map.design->img_height);
	if (!map.c)
		error_exit("Failed to load the Cs");
	map.e = mlx_xpm_file_to_image(game.mlx, "graphics/e.xpm", &map.design->img_width, &map.design->img_height);
	if (!map.e)
		error_exit("Failed to load the Es");
	map.p = mlx_xpm_file_to_image(game.mlx, "graphics/p.xpm", &map.design->img_width, &map.design->img_height);
	if (!map.p)
		error_exit("Failed to load the Ps");
	game.win = mlx_new_window(game.mlx, width * map.design->img_width, height * map.design->img_height, "Nom du jeu");
	if (!game.win)
		error_exit("Failed to create window");
	game.map = &map;
	display_map(&game, &map);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_key_hook(game.win, key_press, &game);
	mlx_loop(game.mlx);
	return (0);
}
