#include "../include/so_long.h"

int	close_window(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free(game->map->design);
	exit(0);
	return (0);
}

void	error_exit(char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

void	initialize_images(t_game *game, t_map *map)
{
	map->zero = mlx_xpm_file_to_image(game->mlx, "graphics/0.xpm",
			&map->design->img_width, &map->design->img_height);
	map->one = mlx_xpm_file_to_image(game->mlx, "graphics/1.xpm",
			&map->design->img_width, &map->design->img_height);
	map->c = mlx_xpm_file_to_image(game->mlx, "graphics/c.xpm",
			&map->design->img_width, &map->design->img_height);
	map->e = mlx_xpm_file_to_image(game->mlx, "graphics/e.xpm",
			&map->design->img_width, &map->design->img_height);
	map->p = mlx_xpm_file_to_image(game->mlx, "graphics/p.xpm",
			&map->design->img_width, &map->design->img_height);
	if (!map->zero || !map->one || !map->c || !map->e || !map->p)
		error_exit("Failed to load images");
}

void	initialize_game(t_game *game, t_map *map, t_game_init *init)
{
	map->design = malloc(sizeof(t_design));
	if (!map->design)
		error_exit("Failed to allocate memory for map design");
	game->mlx = mlx_init();
	if (!game->mlx)
		error_exit("Failed to initialize mlx");
	initialize_images(game, map);
	game->win = mlx_new_window(game->mlx, init->width * map->design->img_width,
			init->height * map->design->img_height, "Nom du jeu");
	if (!game->win)
		error_exit("Failed to create window");
	game->map = map;
}

int	main(int argc, char **argv)
{
	t_game_init	init;
	t_game		game;
	t_map		map;

	if (argc != 2)
		return (printf("Usage: %s <map.ber>\n", argv[0]), 1);
	map.map_file = argv[1];
	get_map_size(map.map_file, &init.width, &init.height);
	initialize_game(&game, &map, &init);
	display_map(&game, &map);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_key_hook(game.win, key_press, &game);
	mlx_loop(game.mlx);
	return (0);
}
