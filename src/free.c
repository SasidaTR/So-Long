/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trischma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:57:11 by trischma          #+#    #+#             */
/*   Updated: 2024/07/11 15:57:29 by trischma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	free_design(t_design *design, void *mlx)
{
	int	i;

	if (design->player_img_up)
		mlx_destroy_image(mlx, design->player_img_up);
	if (design->player_img_down)
		mlx_destroy_image(mlx, design->player_img_down);
	if (design->player_img_left)
		mlx_destroy_image(mlx, design->player_img_left);
	if (design->player_img_right)
		mlx_destroy_image(mlx, design->player_img_right);
	i = 0;
	while (i < NUM_SPRITES)
	{
		if (design->m_imgs[i])
			mlx_destroy_image(mlx, design->m_imgs[i]);
		i++;
	}
	free(design);
}

void	free_map_images(t_map *map, void *mlx)
{
	if (map->zero)
		mlx_destroy_image(mlx, map->zero);
	if (map->one)
		mlx_destroy_image(mlx, map->one);
	if (map->c)
		mlx_destroy_image(mlx, map->c);
	if (map->e)
		mlx_destroy_image(mlx, map->e);
	if (map->m)
		mlx_destroy_image(mlx, map->m);
}

void	free_game_resources(t_game *game)
{
	if (game->map)
	{
		if (game->map->design)
			free_design(game->map->design, game->mlx);
		free_map_images(game->map, game->mlx);
		free_map(game->map);
	}
	if (game->win)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
}
