/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trischma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:53:07 by trischma          #+#    #+#             */
/*   Updated: 2024/07/11 14:53:08 by trischma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	update_monster_animation(t_game *game)
{
	static int	frame_count = 0;

	frame_count++;
	if (frame_count >= 100000)
	{
		game->map->design->current_monster_img++;
		if (game->map->design->current_monster_img >= NUM_SPRITES)
			game->map->design->current_monster_img = 0;
		display_map(game, game->map);
		frame_count = 0;
	}
	return (0);
}

void	initialize_player_and_monster_images(t_game *game, t_map *map)
{
	map->design->player_img_up = mlx_xpm_file_to_image(game->mlx,
			"graf/b.xpm", &map->design->img_width, &map->design->img_height);
	map->design->player_img_down = mlx_xpm_file_to_image(game->mlx,
			"graf/f.xpm", &map->design->img_width, &map->design->img_height);
	map->design->player_img_left = mlx_xpm_file_to_image(game->mlx,
			"graf/l.xpm", &map->design->img_width, &map->design->img_height);
	map->design->player_img_right = mlx_xpm_file_to_image(game->mlx,
			"graf/r.xpm", &map->design->img_width, &map->design->img_height);
	map->design->current_player_img = map->design->player_img_down;
	map->design->m_imgs[0] = mlx_xpm_file_to_image(game->mlx, "graf/mb.xpm",
			&map->design->img_width, &map->design->img_height);
	map->design->m_imgs[1] = mlx_xpm_file_to_image(game->mlx, "graf/ml.xpm",
			&map->design->img_width, &map->design->img_height);
	map->design->m_imgs[2] = mlx_xpm_file_to_image(game->mlx, "graf/mf.xpm",
			&map->design->img_width, &map->design->img_height);
	map->design->m_imgs[3] = mlx_xpm_file_to_image(game->mlx, "graf/mr.xpm",
			&map->design->img_width, &map->design->img_height);
	if (!map->design->player_img_up || !map->design->player_img_down
		|| !map->design->player_img_left || !map->design->player_img_right
		|| !map->design->m_imgs[0] || !map->design->m_imgs[1]
		|| !map->design->m_imgs[2] || !map->design->m_imgs[3])
		error_exit("Failed to load player or monster images");
}

void	initialize_map_images(t_game *game, t_map *map)
{
	map->zero = mlx_xpm_file_to_image(game->mlx, "graf/0.xpm",
			&map->design->img_width, &map->design->img_height);
	map->one = mlx_xpm_file_to_image(game->mlx, "graf/1.xpm",
			&map->design->img_width, &map->design->img_height);
	map->c = mlx_xpm_file_to_image(game->mlx, "graf/c.xpm",
			&map->design->img_width, &map->design->img_height);
	map->e = mlx_xpm_file_to_image(game->mlx, "graf/e.xpm",
			&map->design->img_width, &map->design->img_height);
	map->m = mlx_xpm_file_to_image(game->mlx, "graf/m.xpm",
			&map->design->img_width, &map->design->img_height);
	if (!map->zero || !map->one || !map->c || !map->e || !map->m)
		error_exit("Failed to load map images");
}

void	initialize_game(t_game *game, t_map *map)
{
	map->design = malloc(sizeof(t_design));
	if (!map->design)
		error_exit("Failed to allocate memory for map design");
	game->mlx = mlx_init();
	if (!game->mlx)
		error_exit("Failed to initialize mlx");
	initialize_map_images(game, map);
	initialize_player_and_monster_images(game, map);
	game->win = mlx_new_window(game->mlx, map->width * map->design->img_width,
			map->height * map->design->img_height, "Nom du jeu");
	if (!game->win)
		error_exit("Failed to create window");
	game->map = map;
	game->count->move_count = 0;
}

int	main(int argc, char **argv)
{
	t_game		game;
	t_map		map;
	t_count		count;

	if (argc != 2)
		return (ft_printf("Usage: %s <map.ber>\n", argv[0]), 1);
	map.map_file = argv[1];
	get_map_size(map.map_file, &map);
	validate_map_border(&map);
	count_things(&map, &count);
	game.collectables = 0;
	game.total_collectables = count.collectables;
	game.count = &count;
	initialize_game(&game, &map);
	display_map(&game, &map);
	validate_map_playable(&game, &map);
	mlx_loop_hook(game.mlx, update_monster_animation, &game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_key_hook(game.win, key_press, &game);
	mlx_loop(game.mlx);
	return (0);
}
