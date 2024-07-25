#include "../include/so_long.h"

int	is_valid(int x, int y, t_map *map, int **visited)
{
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
		return (0);
	if (map->map[y][x] == '1' || map->map[y][x] == 'M' || visited[y][x])
		return (0);
	return (1);
}

int	dfs(int x, int y, t_map *map, t_dfs *params)
{
	if (map->map[y][x] == params->target)
		return (1);
	if (map->map[y][x] == 'C')
		(*(params->collectibles))++;
	params->visited[y][x] = 1;
	if (is_valid(x + 1, y, map, params->visited) && dfs(x + 1, y, map, params))
		return (1);
	if (is_valid(x - 1, y, map, params->visited) && dfs(x - 1, y, map, params))
		return (1);
	if (is_valid(x, y + 1, map, params->visited) && dfs(x, y + 1, map, params))
		return (1);
	if (is_valid(x, y - 1, map, params->visited) && dfs(x, y - 1, map, params))
		return (1);
	return (0);
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

int	**allocate_visited(t_gmc *gmc)
{
	int	**visited;
	int	i;

	visited = (int **)malloc(gmc->map->height * sizeof(int *));
	if (!visited)
		error_exit(gmc, "Failed to allocate memory for visited");
	i = 0;
	while (i < gmc->map->height)
	{
		visited[i] = (int *)malloc(gmc->map->width * sizeof(int));
		if (!visited[i])
			error_exit(gmc, "Failed to allocate memory for visited row");
		i++;
	}
	return (visited);
}

void	validate_map_playable(t_gmc *gmc)
{
	int		collectibles_count;
	t_dfs	params;

	params.visited = allocate_visited(gmc);
	initialize_visited(params.visited, gmc->map->height, gmc->map->width);
	collectibles_count = 0;
	params.collectibles = &collectibles_count;
	if (gmc->count->collectables > 0)
	{
		params.target = ' ';
		dfs(gmc->game->player_x, gmc->game->player_y, gmc->map, &params);
		if (collectibles_count != gmc->count->collectables)
		{
			free_visited(params.visited, gmc->map->height);
			error_exit(gmc, "Not all collectibles are reachable");
		}
	}
	initialize_visited(params.visited, gmc->map->height, gmc->map->width);
	params.target = 'E';
	if (!dfs(gmc->game->player_x, gmc->game->player_y, gmc->map, &params))
	{
		free_visited(params.visited, gmc->map->height);
		error_exit(gmc, "No valid path from P to E");
	}
	free_visited(params.visited, gmc->map->height);
}
