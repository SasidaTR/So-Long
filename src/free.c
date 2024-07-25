#include "../include/so_long.h"

void	free_visited(int **visited, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		if (visited[i])
			free(visited[i]);
		i++;
	}
	free(visited);
}

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	if (map->map)
	{
		while (map->map[i])
			free(map->map[i++]);
		free(map->map);
	}
}

void	free_design(t_gmc *gmc)
{
	int	i;

	if (gmc->map->design->player_img_up)
		mlx_destroy_image(gmc->game->mlx, gmc->map->design->player_img_up);
	if (gmc->map->design->player_img_down)
		mlx_destroy_image(gmc->game->mlx, gmc->map->design->player_img_down);
	if (gmc->map->design->player_img_left)
		mlx_destroy_image(gmc->game->mlx, gmc->map->design->player_img_left);
	if (gmc->map->design->player_img_right)
		mlx_destroy_image(gmc->game->mlx, gmc->map->design->player_img_right);
	i = 0;
	while (i < NUM_SPRITES)
	{
		if (gmc->map->design->m_imgs[i])
			mlx_destroy_image(gmc->game->mlx, gmc->map->design->m_imgs[i]);
		i++;
	}
	free(gmc->map->design);
}

void	free_map_images(t_gmc *gmc)
{
	if (gmc->map->zero)
		mlx_destroy_image(gmc->game->mlx, gmc->map->zero);
	if (gmc->map->one)
		mlx_destroy_image(gmc->game->mlx, gmc->map->one);
	if (gmc->map->c)
		mlx_destroy_image(gmc->game->mlx, gmc->map->c);
	if (gmc->map->e)
		mlx_destroy_image(gmc->game->mlx, gmc->map->e);
	if (gmc->map->m)
		mlx_destroy_image(gmc->game->mlx, gmc->map->m);
}

void	free_game_resources(t_gmc *gmc)
{
	if (gmc->map->map)
	{
		if (gmc->map->design)
			free_design(gmc);
		free_map_images(gmc);
		free_map(gmc->map);
	}
	if (gmc->game->win)
	{
		mlx_destroy_window(gmc->game->mlx, gmc->game->win);
		gmc->game->win = NULL;
	}
	if (gmc->game->mlx)
	{
		mlx_destroy_display(gmc->game->mlx);
		free(gmc->game->mlx);
		gmc->game->mlx = NULL;
	}
	if (gmc->game)
		free(gmc->game);
	if (gmc->map)
		free(gmc->map);
	if (gmc->count)
		free(gmc->count);
}
