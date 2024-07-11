/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trischma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:53:15 by trischma          #+#    #+#             */
/*   Updated: 2024/07/11 14:53:16 by trischma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

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

void	count_things(t_map *map, t_count *count)
{
	int	y;
	int	x;

	y = 0;
	count->collectables = 0;
	count->players = 0;
	count->exits = 0;
	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x])
		{
			if (map->map[y][x] == 'C')
				count->collectables++;
			else if (map->map[y][x] == 'P')
				count->players++;
			else if (map->map[y][x] == 'E')
				count->exits++;
			x++;
		}
		y++;
	}
	if (count->players != 1 || count->exits != 1)
		error_exit("Map must contain exactly one 'P' and one 'E'");
}

int	close_window(t_game *game)
{
	if (game->map->design)
	{
		if (game->map->design->player_img_up)
			mlx_destroy_image(game->mlx, game->map->design->player_img_up);
		if (game->map->design->player_img_down)
			mlx_destroy_image(game->mlx, game->map->design->player_img_down);
		if (game->map->design->player_img_left)
			mlx_destroy_image(game->mlx, game->map->design->player_img_left);
		if (game->map->design->player_img_right)
			mlx_destroy_image(game->mlx, game->map->design->player_img_right);
		free(game->map->design);
	}
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	exit(0);
	return (0);
}

void	error_exit(char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}
