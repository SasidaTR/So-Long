#include "../include/so_long.h"

void	initialize_images(t_game *game, t_map *map)
{
	map->zero = mlx_xpm_file_to_image(game->mlx, "graf/0.xpm",
			&map->design->img_width, &map->design->img_height);
	map->one = mlx_xpm_file_to_image(game->mlx, "graf/1.xpm",
			&map->design->img_width, &map->design->img_height);
	map->c = mlx_xpm_file_to_image(game->mlx, "graf/c.xpm",
			&map->design->img_width, &map->design->img_height);
	map->e = mlx_xpm_file_to_image(game->mlx, "graf/e.xpm",
			&map->design->img_width, &map->design->img_height);
	map->design->player_img_up = mlx_xpm_file_to_image(game->mlx,
			"graf/b.xpm", &map->design->img_width, &map->design->img_height);
	map->design->player_img_down = mlx_xpm_file_to_image(game->mlx,
			"graf/f.xpm", &map->design->img_width, &map->design->img_height);
	map->design->player_img_left = mlx_xpm_file_to_image(game->mlx,
			"graf/l.xpm", &map->design->img_width, &map->design->img_height);
	map->design->player_img_right = mlx_xpm_file_to_image(game->mlx,
			"graf/r.xpm", &map->design->img_width, &map->design->img_height);
	map->design->current_player_img = map->design->player_img_down;
	if (!map->zero || !map->one || !map->c || !map->e
		|| !map->design->player_img_up || !map->design->player_img_down
		|| !map->design->player_img_left || !map->design->player_img_right)
		error_exit("Failed to load images");
}

void	initialize_game(t_game *game, t_map *map)
{
	map->design = malloc(sizeof(t_design));
	if (!map->design)
		error_exit("Failed to allocate memory for map design");
	game->mlx = mlx_init();
	if (!game->mlx)
		error_exit("Failed to initialize mlx");
	initialize_images(game, map);
	game->win = mlx_new_window(game->mlx, map->width * map->design->img_width,
			map->height * map->design->img_height, "Nom du jeu");
	if (!game->win)
		error_exit("Failed to create window");
	game->map = map;
	game->count->move_count = 0;
}

void	validate_map_border(t_map *map)
{
	int	x;
	int	y;

	map->width = 0;
	while (map->map[0][map->width])
		(map->width)++;
	map->height = 0;
	while (map->map[map->height])
		(map->height)++;
	x = 0;
	while (x < map->width)
	{
		if (map->map[0][x] != '1' || map->map[map->height - 1][x] != '1')
			error_exit("Error: map borders");
		x++;
	}
	y = 0;
	while (y < map->height)
	{
		if (map->map[y][0] != '1' || map->map[y][map->width - 1] != '1')
			error_exit("Error: map borders");
		y++;
	}
}

int	main(int argc, char **argv)
{
	t_game		game;
	t_map		map;
	t_count		count;

	if (argc != 2)
		return (printf("Usage: %s <map.ber>\n", argv[0]), 1);
	map.map_file = argv[1];
	get_map_size(map.map_file, &map);
	validate_map_border(&map);
	count_things(&map, &count);
	game.collectables = 0;
	game.total_collectables = count.collectables;
	game.count = &count;
	initialize_game(&game, &map);
	display_map(&game, &map);
	validate_map_playable(&game, &map);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_key_hook(game.win, key_press, &game);
	mlx_loop(game.mlx);
	return (0);
}
