#include "../include/so_long.h"

void	count_things(t_map *map, t_counts *counts)
{
	int y;
	int x;

	y = 0;
	counts->collectables = 0;
	counts->players = 0;
	counts->exits = 0;
	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x])
		{
			if (map->map[y][x] == 'C')
				counts->collectables++;
			else if (map->map[y][x] == 'P')
				counts->players++;
			else if (map->map[y][x] == 'E')
				counts->exits++;
			x++;
		}
		y++;
	}
	if (counts->players != 1 || counts->exits != 1)
		error_exit("Map must contain exactly one 'P' and one 'E'");
}

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

void	dfs(t_map *map, int **visited, int x, int y)
{
	if (x < 0 || y < 0 || x >= map->width || y >= map->height)
		return;
	if (map->map[y][x] == '1' || visited[y][x])
		return;
	visited[y][x] = 1;

	dfs(map, visited, x + 1, y);
	dfs(map, visited, x - 1, y);
	dfs(map, visited, x, y + 1);
	dfs(map, visited, x, y - 1);
}

int	is_path_valid(t_map *map)
{
	int	**visited;
	int	y;
	int	x;
	int	found_exit;

	visited = malloc(sizeof(int *) * map->height);
	y = 0;
	while (y < map->height)
	{
		visited[y] = malloc(sizeof(int) * map->width);
		x = 0;
		while (x < map->width)
		{
			visited[y][x] = 0;
			x++;
		}
		y++;
	}
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->map[y][x] == 'P')
			{
				dfs(map, visited, x, y);
				break;
			}
			x++;
		}
		y++;
	}
	found_exit = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->map[y][x] == 'C' && !visited[y][x])
				return 0;
			if (map->map[y][x] == 'E' && visited[y][x])
				found_exit = 1;
			x++;
		}
		y++;
	}
	y = 0;
	while (y < map->height)
	{
		free(visited[y]);
		y++;
	}
	free(visited);

	return found_exit;
}
