#include "../include/so_long.h"

int	is_valid(int x, int y, t_map *map, int **visited)
{
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
		return (0);
	if (map->map[y][x] == '1' || visited[y][x])
		return (0);
	return (1);
}

int	dfs(int x, int y, t_map *map, int **visited, char target)
{
	if (map->map[y][x] == target)
		return (1);
	visited[y][x] = 1;
	if (is_valid(x + 1, y, map, visited) && dfs(x + 1, y, map, visited, target))
		return (1);
	if (is_valid(x - 1, y, map, visited) && dfs(x - 1, y, map, visited, target))
		return (1);
	if (is_valid(x, y + 1, map, visited) && dfs(x, y + 1, map, visited, target))
		return (1);
	if (is_valid(x, y - 1, map, visited) && dfs(x, y - 1, map, visited, target))
		return (1);
	return (0);
}

int **allocate_visited(int height, int width)
{
	int	**visited;
	int	i;
	
	visited = (int **)malloc(height * sizeof(int *));
	i = 0;
	while (i < height)
	{
		visited[i] = (int *)malloc(width * sizeof(int));
		i++;
	}
	return visited;
}

void initialize_visited(int **visited, int height, int width)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			visited[i][j] = 0;
			j++;
		}
		i++;
	}
}

void find_start(t_map *map, int *start_x, int *start_y)
{
	int i;
	int j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->map[i][j] == 'P')
			{
				*start_x = j;
				*start_y = i;
				return;
			}
			j++;
		}
		i++;
	}
}

void validate_map_playable(t_map *map)
{
	int	**visited;
	int	start_x;
	int	start_y;

	visited = allocate_visited(map->height, map->width);
	initialize_visited(visited, map->height, map->width);
	find_start(map, &start_x, &start_y);
	if (!dfs(start_x, start_y, map, visited, 'C'))
		error_exit("No valid path from P to C");
	initialize_visited(visited, map->height, map->width);
	if (!dfs(start_x, start_y, map, visited, 'E'))
		error_exit("No valid path from P to E");
	for (int i = 0; i < map->height; i++)
		free(visited[i]);
	free(visited);
}

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
	validate_map_playable(&map);
	display_map(&game, &map);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_key_hook(game.win, key_press, &game);
	mlx_loop(game.mlx);
	return (0);
}
