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
