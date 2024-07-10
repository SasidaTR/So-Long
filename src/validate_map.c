#include "../include/so_long.h"

int	is_valid(int x, int y, t_map *map, int **visited)
{
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
		return (0);
	if (map->map[y][x] == '1' || visited[y][x])
		return (0);
	return (1);
}

int	dfs(int x, int y, t_map *map, int **visited, char target, int *collectibles)
{
	if (map->map[y][x] == target)
		return (1);
	if (map->map[y][x] == 'C')
		(*collectibles)++;
	visited[y][x] = 1;
	if (is_valid(x + 1, y, map, visited) && dfs(x + 1, y,
			map, visited, target, collectibles))
		return (1);
	if (is_valid(x - 1, y, map, visited) && dfs(x - 1, y,
			map, visited, target, collectibles))
		return (1);
	if (is_valid(x, y + 1, map, visited) && dfs(x, y + 1,
			map, visited, target, collectibles))
		return (1);
	if (is_valid(x, y - 1, map, visited) && dfs(x, y - 1,
			map, visited, target, collectibles))
		return (1);
	return (0);
}

int	**allocate_visited(int height, int width)
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
	return (visited);
}

void	initialize_visited(int **visited, int height, int width)
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

void	validate_map_playable(t_game *game, t_map *map)
{
	int	**visited;
	int	i;
	int	collectibles_count;

	visited = allocate_visited(map->height, map->width);
	initialize_visited(visited, map->height, map->width);
	collectibles_count = 0;
	if (game->total_collectables > 0)
	{
		dfs(game->player_x, game->player_y, map, visited,
			' ', &collectibles_count);
		if (collectibles_count != game->total_collectables)
			error_exit("Not all collectibles are reachable");
	}
	initialize_visited(visited, map->height, map->width);
	if (!dfs(game->player_x, game->player_y, map, visited,
			'E', &collectibles_count))
		error_exit("No valid path from P to E");
	i = 0;
	while (i < map->height)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}
