/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trischma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:53:11 by trischma          #+#    #+#             */
/*   Updated: 2024/07/11 14:53:12 by trischma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	put_image_to_window(t_game *game, t_map *map, int x, int y)
{
	if (map->map[y][x] == '0')
		mlx_put_image_to_window(game->mlx, game->win, map->zero,
			x * map->design->img_width, y * map->design->img_height);
	else if (map->map[y][x] == '1')
		mlx_put_image_to_window(game->mlx, game->win, map->one,
			x * map->design->img_width, y * map->design->img_height);
	else if (map->map[y][x] == 'C')
		mlx_put_image_to_window(game->mlx, game->win, map->c,
			x * map->design->img_width, y * map->design->img_height);
	else if (map->map[y][x] == 'E')
		mlx_put_image_to_window(game->mlx, game->win, map->e,
			x * map->design->img_width, y * map->design->img_height);
	else if (map->map[y][x] == 'M')
		mlx_put_image_to_window(game->mlx, game->win,
			map->design->m_imgs[map->design->current_monster_img],
			x * map->design->img_width, y * map->design->img_height);
	else if (map->map[y][x] == 'P')
	{
		mlx_put_image_to_window(game->mlx, game->win,
			map->design->current_player_img, x * map->design->img_width,
			y * map->design->img_height);
		game->player_x = x;
		game->player_y = y;
	}
}

void	display_map(t_game *game, t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x])
		{
			put_image_to_window(game, map, x, y);
			x++;
		}
		y++;
	}
}

void	read_map_line(t_game *game, int fd, t_map *map, int *line_count)
{
	char	*line;
	char	**temp;

	while (get_next_line(fd, &line) > 0)
	{
		temp = realloc(map->map, sizeof(char *) * (*line_count + 2));
		if (!temp)
		{
			free(line);
			error_exit(game, "Failed to reallocate memory for map content");
		}
		map->map = temp;
		map->map[*line_count] = ft_strdup(line);
		if (!map->map[*line_count])
		{
			free(line);
			error_exit(game, "Failed to allocate memory for map content line");
		}
		free(line);
		(*line_count)++;
	}
}

void	get_map_size(t_game *game, char *file, t_map *map)
{
	int		fd;
	int		line_count;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_exit(game, "Failed to open map file");
	map->map = NULL;
	line_count = 0;
	read_map_line(game, fd, map, &line_count);
	if (line_count > 0)
		map->map[line_count] = NULL;
	close(fd);
}

void	find_player_position(t_game *game, t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x])
		{
			if (map->map[y][x] == 'P')
			{
				game->player_x = x;
				game->player_y = y;
				return ;
			}
			x++;
		}
		y++;
	}
	error_exit_two(game, map, "Player position not found");
}
