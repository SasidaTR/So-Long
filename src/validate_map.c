/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trischma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:53:14 by trischma          #+#    #+#             */
/*   Updated: 2024/07/12 11:18:43 by trischma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	**allocate_visited(t_game *game, int height, int width)
{
	int	**visited;
	int	i;

	visited = (int **)malloc(height * sizeof(int *));
	if (!visited)
		error_exit(game, "Failed to allocate memory for visited");
	i = 0;
	while (i < height)
	{
		visited[i] = (int *)malloc(width * sizeof(int));
		if (!visited[i])
			error_exit(game, "Failed to allocate memory for visited row");
		i++;
	}
	return (visited);
}

void	validate_map_playable(t_game *game, t_map *map)
{
	int		collectibles_count;
	t_dfs	params;

	params.visited = allocate_visited(game, map->height, map->width);
	initialize_visited(params.visited, map->height, map->width);
	collectibles_count = 0;
	params.collectibles = &collectibles_count;
	if (game->total_collectables > 0)
	{
		params.target = ' ';
		dfs(game->player_x, game->player_y, map, &params);
		if (collectibles_count != game->total_collectables)
		{
			free_visited(params.visited, map->height);
			error_exit(game, "Not all collectibles are reachable");
		}
	}
	initialize_visited(params.visited, map->height, map->width);
	params.target = 'E';
	if (!dfs(game->player_x, game->player_y, map, &params))
	{
		free_visited(params.visited, map->height);
		error_exit(game, "No valid path from P to E");
	}
	free_visited(params.visited, map->height);
}
