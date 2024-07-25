#include "../include/so_long.h"

int	close_window(t_gmc *gmc)
{
	free_game_resources(gmc);
	exit(0);
	return (0);
}

void	error_exit(t_gmc *gmc, char *message)
{
	free_game_resources(gmc);
	perror(message);
	exit(EXIT_FAILURE);
}

void	count_things(t_gmc *gmc)
{
	int	y;
	int	x;

	y = 0;
	gmc->count->collectables = 0;
	gmc->count->players = 0;
	gmc->count->exits = 0;
	while (gmc->map->map[y])
	{
		x = 0;
		while (gmc->map->map[y][x])
		{
			if (gmc->map->map[y][x] == 'C')
				gmc->count->collectables++;
			else if (gmc->map->map[y][x] == 'P')
				gmc->count->players++;
			else if (gmc->map->map[y][x] == 'E')
				gmc->count->exits++;
			x++;
		}
		y++;
	}
	if (gmc->count->players != 1 || gmc->count->exits != 1
		|| gmc->count->collectables < 1)
		error_exit(gmc, "Need only 1 'P', 1 'E' and at least 1 'C'");
}

void	validate_map_border(t_gmc *gmc)
{
	int	x;
	int	y;

	gmc->map->width = 0;
	while (gmc->map->map[0][gmc->map->width])
		(gmc->map->width)++;
	gmc->map->height = 0;
	while (gmc->map->map[gmc->map->height])
		(gmc->map->height)++;
	x = 0;
	while (x < gmc->map->width)
	{
		if (gmc->map->map[0][x] != '1'
			|| gmc->map->map[gmc->map->height - 1][x] != '1')
			error_exit(gmc, "Error: map borders");
		x++;
	}
	y = 0;
	while (y < gmc->map->height)
	{
		if (gmc->map->map[y][0] != '1'
			|| gmc->map->map[y][gmc->map->width - 1] != '1')
			error_exit(gmc, "Error: map borders");
		y++;
	}
}
