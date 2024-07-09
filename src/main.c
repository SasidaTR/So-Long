#include "../include/so_long.h"

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
	game->player_img_up = mlx_xpm_file_to_image(game->mlx, "graphics/b.xpm",
			&map->design->img_width, &map->design->img_height);
	game->player_img_down = mlx_xpm_file_to_image(game->mlx, "graphics/f.xpm",
			&map->design->img_width, &map->design->img_height);
	game->player_img_left = mlx_xpm_file_to_image(game->mlx, "graphics/l.xpm",
			&map->design->img_width, &map->design->img_height);
	game->player_img_right = mlx_xpm_file_to_image(game->mlx, "graphics/r.xpm",
			&map->design->img_width, &map->design->img_height);
	game->current_player_img = game->player_img_down;
	if (!map->zero || !map->one || !map->c || !map->e
		|| !game->player_img_up || !game->player_img_down
		|| !game->player_img_left || !game->player_img_right)
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

void	validate_map_border(t_map *map, int *width, int *height)
{
	int	x;
	int	y;

	*width = 0;
	while (map->map[0][*width])
		(*width)++;
	*height = 0;
	while (map->map[*height])
		(*height)++;
	x = 0;
	while (x < *width)
	{
		if (map->map[0][x] != '1' || map->map[*height - 1][x] != '1')
			error_exit("Error: map borders");
		x++;
	}
	y = 0;
	while (y < *height)
	{
		if (map->map[y][0] != '1' || map->map[y][*width - 1] != '1')
			error_exit("Error: map borders");
		y++;
	}
}

int	main(int argc, char **argv)
{
	t_game_init	init;
	t_game		game;
	t_map		map;
	t_counts	counts;

	if (argc != 2)
		return (printf("Usage: %s <map.ber>\n", argv[0]), 1);
	map.map_file = argv[1];
	get_map_size(map.map_file, &map);
	validate_map_border(&map, &init.width, &init.height);
	count_things(&map, &counts);
	game.collectables = 0;
	game.total_collectables = counts.collectables;
	initialize_game(&game, &map, &init);
	display_map(&game, &map);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_key_hook(game.win, key_press, &game);
	mlx_loop(game.mlx);
	return (0);
}
