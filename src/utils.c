#include "../include/so_long.h"

void	count_things(t_map *map, t_counts *counts)
{
	int	y;
	int	x;

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
